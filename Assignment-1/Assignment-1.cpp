#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;

typedef struct _coeff{
    float coefficient;//stores coefficient of the term
    int degree;//stores degree of the term
    struct _coeff *next;
}coeff;//this is used to store terms of a particular polynomial

typedef struct poly{
    coeff *coefficients;//stores head pointer of the linked list of the terms
    coeff *coefficientsend;//stores end pointer of the linked list of the terms
    int id;//stores id of the polynomial
    struct poly *next;
}polynomial;//this is used to store linked list of polynomials

void printPoly(polynomial *poly)//this function is used to print all the polynomials in the linked list poly which is passed to it
{
    polynomial *b;//used to traverse the list of polynomials
    b= poly;
    int i,j;
    cout<<"\nId\t|\tPolynomial\n";
    if(b==NULL){
        cout<<"No polynomials to show\n";
        return;
    }
    while(b!=NULL){
        string str = "";
        int z = b->id,i=0,j;
        if(z<0) i++;
        while(z!=0){
            i++;
            z = z/10;
        }
        for(i=i;i<=7;i++){
            str = str + " ";
        }//this is used to make the output look pretty
        cout<<b->id<<str<<"| ";
        coeff *co;
        co = b->coefficients;
        if(b->coefficients==NULL) cout<<"No terms to show";
        for(j=0;co!=NULL;co=co->next){
                if(j==0){
                    cout<<co->coefficient<<"*x^"<<co->degree;
                    j++;
                }
                else{
                if(co->coefficient>0){
                    cout<<" + "<<co->coefficient<<"*x^"<<co->degree;
                    j++;
                }
                else
                {
                    cout<<" - "<<co->coefficient*(-1)<<"*x^"<<co->degree;
                    j++;
                }
                }
        }
        cout<<"\n";
        b=b->next;
    }
}

polynomial *addremoveterm(polynomial *p1,int d, float c)//this function is used to add terms in to the polynomial p1
{
    if(p1->coefficientsend!=NULL){//this checks whether the polynomial has coefficients defined or not
        coeff *co,*ce,*cp;//co is used to store the new term which is to be created, ce is used to traverse through the list and cp is used to store parent while traversing
        co = (coeff * )malloc(sizeof(coeff));
        co->coefficient = c;
        co->degree = d;
        co->next=NULL;
        if(d>p1->coefficientsend->degree){
            p1->coefficientsend->next = co;
            p1->coefficientsend = p1->coefficientsend->next;
        }
        else{
            if(d < p1->coefficients->degree){
                co->next = p1->coefficients;
                p1->coefficients = co;
                return p1;
            }
            ce = p1->coefficients;
            while(d>ce->degree){
                cp = ce;
                ce = ce->next;
            }
            if(ce->degree == d){
                ce->coefficient=c;
            }
            else{
                co->next = ce;
                cp->next = co;
            }
        }
    }
    else{
        p1->coefficients = (coeff * )malloc(sizeof(coeff));
        p1->coefficients->coefficient = c;
        p1->coefficients->degree = d;
        p1->coefficients->next = NULL;
        p1->coefficientsend = p1->coefficients;
    }
    return p1;
}

polynomial *addremoveterm(polynomial *p1, int d)//this function is used to remove a term from polynomial p1 with degree d
{
    if(p1->coefficientsend!=NULL){//this checks whether the polynomial contain coefficients or not
        if(d>p1->coefficientsend->degree){//it is checking whether the given degree greater than the highest degree of the polynomial
            cout<<"There isn't any term with degree which you have specified\n";
            return p1;
        }
        coeff *ce,*cp;//ce is used to traverse through the list and cp is used to store parent while traversing
        ce = p1->coefficients;
        while(d>ce->degree){
            cp = ce;
            ce = ce->next;
        }
        if(d==ce->degree){
            if(d==p1->coefficientsend->degree){
                p1->coefficientsend = cp;
            }
            if(d==p1->coefficients->degree){
                p1->coefficients = p1->coefficients->next;
                return p1;
            }
            cp->next = ce->next;
            free(ce);
            cout<<"Selected term is deleted succesfully\n";
        }
        else{
            cout<<"There isn't any term with degree which you have specified\n";
        }
        return p1;
    }
    else{
        cout<<"There isn't any term with degree which you have specified\n";
        return p1;
    }
}

polynomial *addremoveterm(polynomial *p1, float i = 0, float j = 0, double e = 1e-9)//this function remove all the terms with absolute coefficient values less than epsillon in list p1
{
    coeff *ce;//used to traverse the list p1
    ce = p1->coefficients;
    int I=0;//used as flag to check whether there are any terms which satisfies the required terms
    while(ce!=NULL){
        if(ce->coefficient<0){//checks whether the coefficient is negative
            if(ce->coefficient*(-1)<e){
                p1 = addremoveterm(p1, ce->degree);//removes the term
                I++;
            }
        }
        else{
            if(ce->coefficient<e){
                p1 = addremoveterm(p1, ce->degree);//removes the term
                I++;
            }
        }
        ce = ce->next;
    }
    if(I) cout<<"All the terms with absolute coefficient less than "<<e<<" are removed\n";
    else cout<<"There are no terms with absolute coefficient less than "<<e<<" to be removed\n";
    return p1;
}

double evaluate(polynomial *p1, double x)//this function evaluates the polynomial p1 with the value x
{
    double value=0;
    coeff *ce;//used to traverse through the list of terms
    ce = p1->coefficients;
    int i=0;
    while(ce!=NULL){
        value= value + (ce->coefficient)*pow(x , ce->degree);
        i++;
        ce = ce->next;
    }
    if(!i) cout<<"There aren't any terms in the polynomial to evaluate\n";
    return value;
}

polynomial operator+(polynomial a, polynomial b){//this overloading of the operator is done to add two polynomials using '+' symbol
    coeff *c1,*c2,*head=NULL,*c;//c1 is used to store the list of terms in polynomial a c2 to store terms of b head to store the head pointer of the list of terms which are created after adding a, b
    c1 = a.coefficients;
    c2 = b.coefficients;
    while(c1!=NULL && c2!=NULL){
        if(c1->degree == c2->degree){
            if(head == NULL){
                head = (coeff *)malloc(sizeof(coeff));
                head->coefficient = c1->coefficient + c2->coefficient;
                head->degree = c1->degree;
                head->next = NULL;
                c = head;
            }
            else{
                c->next = (coeff *)malloc(sizeof(coeff));
                c->next->coefficient = c1->coefficient + c2->coefficient;
                c->next->degree = c1->degree;
                c->next->next = NULL;
                c = c->next;
            }
            c1 = c1->next;
            c2 = c2->next;
        }
        else{
            if(c1->degree>c2->degree){
                if(head == NULL){
                    head = (coeff *)malloc(sizeof(coeff));
                    head->coefficient = c2->coefficient;
                    head->degree = c2->degree;
                    head->next = NULL;
                    c = head;
                }
                else{
                    c->next = (coeff *)malloc(sizeof(coeff));
                    c->next->coefficient = c2->coefficient;
                    c->next->degree = c2->degree;
                    c->next->next = NULL;
                    c = c->next;
                }
                c2 = c2->next;
            }
            else{
                if(head == NULL){
                    head = (coeff *)malloc(sizeof(coeff));
                    head->coefficient = c1->coefficient;
                    head->degree = c1->degree;
                    head->next = NULL;
                    c = head;
                }
                else{
                    c->next = (coeff *)malloc(sizeof(coeff));
                    c->next->coefficient = c1->coefficient;
                    c->next->degree = c1->degree;
                    c->next->next = NULL;
                    c = c->next;
                }
                c1 = c1->next;
            }
        }
    }
    while(c1!=NULL){
        if(head == NULL){
                    head = (coeff *)malloc(sizeof(coeff));
                    head->coefficient = c1->coefficient;
                    head->degree = c1->degree;
                    head->next = NULL;
                    c = head;
                }
                else{
                    c->next = (coeff *)malloc(sizeof(coeff));
                    c->next->coefficient = c1->coefficient;
                    c->next->degree = c1->degree;
                    c->next->next = NULL;
                    c = c->next;
                }
                c1 = c1->next;
    }
    while(c2!=NULL){
        if(head == NULL){
                    head = (coeff *)malloc(sizeof(coeff));
                    head->coefficient = c2->coefficient;
                    head->degree = c2->degree;
                    head->next = NULL;
                    c = head;
                }
                else{
                    c->next = (coeff *)malloc(sizeof(coeff));
                    c->next->coefficient = c2->coefficient;
                    c->next->degree = c2->degree;
                    c->next->next = NULL;
                    c = c->next;
                }
                c2 = c2->next;
    }
    polynomial p;
    p.coefficients = head;
    return p;
}

coeff *derivative(polynomial * p)//this function creates a list of coefficients which are derivative of polynomial p
{
    coeff *head=NULL, *c,*ce;
    c = p->coefficients;
    while(c!=NULL){
        if(c->degree){//checks whether the coefficient is a non zero integer
            if(head == NULL){
                head = (coeff *)malloc(sizeof(coeff));
                head->coefficient = c->coefficient*c->degree;
                head->degree= c->degree - 1;
                head->next = NULL;
                ce = head;
            }
            else{
                ce->next = (coeff *)malloc(sizeof(coeff));
                ce->next->coefficient = c->coefficient*c->degree;
                ce->next->degree = c->degree - 1;
                ce->next->next=NULL;
                ce = ce->next;
            }
        }
        c=c->next;
    }
    return head;
}

polynomial *deletePoly(polynomial *p, int id)//this function deleted the polynomial with id = id
{
    polynomial *pe,*pp;
    pe = p;
    while(pe->id!=id){
        pp = pe;
        pe = pe->next;
    }
    pp->next = pe->next;
    free(pe);
    return p;
}

void newton_zero(polynomial *p, double x0 , double eps=1e-9)//this function used to calculate zero of the polynomial using newton method
{
    double x1,vp,vdp;
    int n=1;
    polynomial *dp;
    dp = (polynomial *)malloc(sizeof(polynomial));
    dp->coefficients = derivative(p);
    x1=x0;
    vp = evaluate(p,x0);
    vdp = evaluate(dp,x0);
    x0 = x0 - vp/vdp;
    if(isinf(vdp) || isinf(vp)|| isnan(x0)){//checks if any value evaluated to not a numeric
            cout<<"One of the values evaluated to 1/0 so the process got terminated\n";
            return;
    }
    while(abs(x1-x0)>eps&&n<10000){//if the polynomial doesn't have any zero it exits the loop after 10000 steps
        x1 = x0;
        vp = evaluate(p,x0);
        vdp = evaluate(dp,x0);
        if(vdp == 0){
            cout<<"Couldn't compute Newton zero because one of the derivative which is a denominator became 0\n";
            return;
        }
        if(isinf(vdp) || isinf(vp) || isnan(x0)){
            cout<<"One of the values evaluated to 1/0 so the process got terminated\n";
            return;
        }
        x0 = x0 - vp/vdp;
        n++;
    }
    if(abs(x1-x0)>eps){
        cout<<"There isn't any root for selected polynomial\n";
        return;
    }
    cout<<"One of the zero of selected polynomial is "<<x0<<"\n";
}

int main()
{
    int choice=1,degree,i,Id;
    char c;
    int D;
    float C;
    polynomial *polys=NULL,*polye,*polyb,*polyb1;//polys store head of the list of polynomials, polye stored end pointer of the list, polyb and polyb1 are used arbitarily whenever required
    while(choice){//loop which ends when the user wants to terminate it
        cout<<"_______________________________________________________\n";
        cout<<"Select the task you want to perform from the list below:\n1-Create a polynomial\n2-Add or remove a term from the polynomial\n3-Evaluate a polynomial\n4-Add two polynomials\n5-Differentiate a polynomial\n6-calculate zero of a polynomial using Newton's method\n7-Delete a polynomial\n8-Display polynomial\n0-exit\nYour option:";
        cin>>choice;
        switch(choice){
            case 1://in this case a polynomial is created and default values of coefficients are zero
                cout<<"_______________________________________________________";
                cout<<"\n\tCreating polynomial\n";
                polynomial *p;
                p=(polynomial *)malloc(sizeof(polynomial));
                p->next=NULL;
                p->coefficients = NULL;
                p->coefficientsend = NULL;
                if(polys==NULL){
                    polys=p;
                    polys->id=1;
                    polye=polys;
                }
                else{
                    polye->next = p;
                    polye->next->id = polye->id+1;
                    polye=polye->next;
                }
                cout<<"Polynomial is created succesfully(all the coefficients are initiated to 0 by default)\n";
                break;

            case 2://this case performs add and remove functionalities. It has 3 subcases
                cout<<"_______________________________________________________";
                cout<<"\n\tAdding or removing a term\n";
                cout<<"Select the task you want to perform:\na-Add term\nb-Remove term of degree d\nc-Remove all the terms with absolute coefficient values less than epsillon\nYour choice:";
                cin>>c;
                switch (c)
                {
                case 'a'://In this case new term is added
                    cout<<"_________________________________________________";
                    cout<<"\n\tAdding a term\n";
                    cout<<"Select the id of the polynomial which you want to edit from the list below:";
                    printPoly(polys);//displays all the polynomials
                    if(polys==NULL) break;
                    cout<<"Your choice:";
                    cin>>Id;
                    if(Id>polye->id || Id<polys->id){
                        cout<<"Selected id is invalid\n";
                        break;
                    }
                    cout<<"Degree of the term which you want to add:";
                    cin>>D;
                    cout<<"Co-efficient of the term you want to add:";
                    cin>>C;
                    polyb = polys;
                    i=1;
                    while(polyb->id!=Id){
                        polyb = polyb->next;
                        i++;
                    }
                    polyb = addremoveterm(polyb,D,C);
                    cout<<"Specified term is added successfully\n";
                    break;

                case 'b'://in this case the term with degree d is removed
                    cout<<"_________________________________________________";
                    cout<<"\n\tdeleting a term\n";
                    cout<<"Select the id of the polynomial which you want to edit from the list below:";
                    printPoly(polys);//displays all the polynomials
                    if(polys==NULL) break;
                    cout<<"Your choice:";
                    cin>>Id;
                    if(Id>polye->id || Id<polys->id){
                        cout<<"Selected id is invalid\n";
                        break;
                    }
                    cout<<"Degree of the term which you want to delete:";
                    cin>>D;
                    polyb = polys;
                    i=1;
                    while(polyb->id!=Id){
                        polyb = polyb->next;
                        i++;
                    }
                    polyb = addremoveterm(polyb,D);
                    break;

                case 'c'://in this case all the terms with coefficient less than epsillon are deleted
                    cout<<"_________________________________________________";
                    cout<<"\n\tdeleting a term\n";
                    cout<<"Select the id of the polynomial which you want to edit from the list below:";
                    printPoly(polys);//displays all the polynomials
                    if(polys==NULL) break;
                    cout<<"Your choice:";
                    cin>>Id;
                    if(Id>polye->id || Id<polys->id){
                        cout<<"Selected id is invalid\n";
                        break;
                    }
                    polyb = polys;
                    i=1;
                    while(polyb->id!=Id){
                        polyb = polyb->next;
                        i++;
                    }
                    cout<<"Do you want to specify value of epsillon:\n1-yes\n0-no\nYour choice:";
                    cin>>i;
                    if(i){
                        cout<<"epsillon:";
                        double _epsi;
                        cin>>_epsi;
                        polyb = addremoveterm(polyb,0,0,_epsi);
                    }
                    else polyb = addremoveterm(polyb);
                    break;

                default:
                    cout<<"You have selected an invalid option\n";
                    break;
                }
                break;

            case 3://in this case the polynomial is evaluated
                cout<<"_______________________________________________________";
                cout<<"\n\tEvaluating polynomial\n";
                cout<<"Select the id of the polynomial which you want to evaluate from the list below:";
                printPoly(polys);//displays all the polynomials
                if(polys==NULL) break;
                cout<<"Your choice:";
                cin>>Id;
                if(Id>polye->id || Id<polys->id){
                    cout<<"Selected id is invalid\n";
                    break;
                }
                polyb = polys;
                i=1;
                while(polyb->id!=Id){
                    polyb = polyb->next;
                    i++;
                }
                double x,value;
                cout<<"Your choice of x: ";
                cin>>x;
                value = evaluate(polyb , x);
                if(polyb->coefficients==NULL) break;
                cout<<"Evaluated value = "<<value<<"\n";
                break;

            case 4://in this case a new polynomial is created by adding two polynomials
                polynomial *newP;
                newP = (polynomial *)malloc(sizeof(polynomial));
                cout<<"_______________________________________________________";
                cout<<"\n\tEvaluating polynomial\n";
                cout<<"Select two ids from the polynomials which you want to add from the list below:";
                printPoly(polys);//displays all the polynomials
                if(polys==NULL) break;
                int M,N;
                cout<<"Your 1st choice:";
                cin>>M;
                cout<<"Your 2nd choice:";
                cin>>N;
                if(M<polys->id || M>polye->id || N<polys->id || N>polye->id){
                    cout<<"You have selected an invalid choice\n";
                    break;
                }
                i=1;
                polyb=polys;
                while(polyb->id!=M){
                    polyb = polyb->next;
                    i++;
                }
                i=1;
                polyb1=polys;
                while(polyb1->id!=N){
                    polyb1 = polyb1->next;
                    i++;
                }
                polynomial p1,p2,p3;//p1, p2 are used to convert selected polynomial *'s to polynomial as the operator '+' is overloaded such a way that polynomials can be added and p3 is used to store the polynimial created by adding p1 and p2
                p1.coefficients = polyb1->coefficients;
                p2.coefficients = polyb->coefficients;
                p1.next = NULL;
                p2.next = NULL;
                newP->id = polye->id+1;
                polye->next = newP;
                p3 = p1+p2;
                newP->coefficients = p3.coefficients;
                polye->next = newP;
                polye = polye->next;
                cout<<"Do you want to take a look at new polynomial created by adding the polynomials selected:\n1-yes\n0-no\nYour choice:";
                cin>>i;
                if(i) printPoly(polye);
                break;

            case 5://in this case a new polynomial is created by differentiating a polynomial
                cout<<"_______________________________________________________";
                cout<<"\n\tDifferentiating a polynomial\n";
                cout<<"Select the id of the polynomial which you want to differentiate from the list below:";
                printPoly(polys);//displays all the polynomials
                if(polys==NULL) break;
                cout<<"Your choice:";
                cin>>Id;
                if(Id>polye->id || Id<polys->id){
                    cout<<"Selected id is invalid\n";
                    break;
                }
                polyb = polys;
                i=1;
                while(polyb->id!=Id){
                    polyb = polyb->next;
                    i++;
                }
                if(polyb->coefficients == NULL)
                {
                    cout<<"Selected polynomial cannot be differentiated because there aren't any terms in the polynomials yet\n";
                    break;
                }
                newP = (polynomial *)malloc(sizeof(polynomial));
                newP->id = polye->id+1;
                newP->next = NULL;
                newP->coefficients = derivative(polyb);
                newP->coefficientsend = newP->coefficients;
                while(newP->coefficientsend!=NULL && newP->coefficientsend->next!=NULL){
                    newP->coefficientsend = newP->coefficientsend->next;
                }
                polye->next = newP;
                polye = polye->next;
                cout<<"Do you want to take a look at new polynomial created by differentiating the polynomial selected:\n1-yes\n0-no\nYour choice:";
                cin>>i;
                if(i) printPoly(polye);
                break;

            case 6://in this case zero of the polynomial is calculated using newton's method
                cout<<"_______________________________________________________";
                cout<<"\n\tFinding zero a polynomial\n";
                cout<<"Select the id of the polynomial to which you want to find a zero from the list below:";
                printPoly(polys);//displays all the polynomials
                if(polys==NULL) break;
                cout<<"Your choice:";
                cin>>Id;
                if(Id>polye->id || Id<polys->id){
                    cout<<"Selected id is invalid\n";
                    break;
                }
                polyb = polys;
                i=1;
                while(polyb->id!=Id){
                    polyb = polyb->next;
                    i++;
                }
                if(polyb->coefficients == NULL)
                {
                    cout<<"Zero of the selected polynomial cannot be determined because there aren't any terms in the polynomials yet\n";
                    break;
                }
                double x0,val,epsillon_;
                cout<<"Enter the value from which you want to start the iteration(x0):";
                cin>>x0;
                cout<<"Do you want to specify the epsillon:\n1-YES\n0-NO\nyour choice:";
                cin>>i;
                if(i){
                    cout<<"Your choice for epsillon:";
                    cin>>epsillon_;
                    newton_zero(polyb,x0,epsillon_);
                }
                else newton_zero(p,x0);
                break;

            case 7://in this case selected polynomial is removed from the list
                cout<<"_______________________________________________________";
                cout<<"\n\tDeleting a polynomial\n";
                cout<<"Select the id of the polynomial which you want to delete from the list below:";
                printPoly(polys);//displays all the polynomials
                if(polys==NULL) break;
                cout<<"Your choice:";
                cin>>Id;
                if(Id>polye->id || Id<polys->id){
                    cout<<"Selected id is invalid\n";
                    break;
                }
                if(polys->id == Id){
                    polys = polys->next;
                    cout<<"Selected polynomial is deleted successfully\n";
                    break;
                }
                if(polye->id == Id){
                    polyb = polys;
                    while(polyb->next->next!=NULL){
                        polyb = polyb->next;
                    }
                    polyb->next = NULL;
                    polye = polyb;
                    cout<<"Selected polynomial is deleted successfully\n";
                    break;
                }
                polys = deletePoly(polys,Id);
                cout<<"Selected polynomial is deleted successfully\n";
                break;

            case 8://in this case all the polynomials in the list of polys are displayed
                cout<<"_______________________________________________________";
                cout<<"\n\tDisplaying polynomials\n";
                printPoly(polys);//displays all the polynomials
                break;

            case 0://in this case user is exited from the loop
                cout<<"you are exited\n";
                break;

            default://this is the case where user opts any invalid option i.e, any option which is not listed in the menu
                cout<<"You have selected an invalid opion.Please select a correct option\n";
                break;
        }
    }
    return 0;
}
