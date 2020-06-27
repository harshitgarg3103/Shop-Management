#include<bits/stdc++.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include<string>

//#define f(i,a,n) for(i=a;i<n;i++)
using namespace std;
struct bill
{
    int billid;
    string custname;
    string pname;
    int quantity;
    int price;
    int netamount;
};
struct newproduct
{
    int pno;
	string pname;
	float price;
	int quantity,shelfno,rowno;
	//struct newproduct * left, *  right;
	//newproduct(int a,string b,float c,int d,int shelf,int row):
	  //  pno(a),pname(b),price(c),quantity(d),rowno(row),shelfno(shelf){}
};
//fstream fp;
struct newproduct h[26][100];
//struct newproduct k[26][100];
//fp.open("product.dat",ios::out | ios::in );
//fp.read((char*) &h,sizeof(h));

int hashkey(string s)
{
    int sum=0;
    int key=0;
    for(int j=0;j<s.length();j++)
    {
        sum=sum+int(s[j]);
    }
    key=sum%100;
    return key;

}
void generatebill()
{
    struct bill b;
    int i=0,j,k=0,key=0,flag=0;
    string product_name,cname;
    //ofstream f1;
    FILE *f1;
    fflush(stdin);
    f1=fopen("bill.dat","ab");
    cout<<endl<<"Please Enter The Bill Number: ";
    cin>>b.billid;
    cout<<endl<<"Please Enter The Name of The Customer: ";
    fflush(stdin);
    cin>>b.custname;
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>b.pname;
    transform((b.pname).begin(),(b.pname).end(),(b.pname).begin(),::toupper);
    key=hashkey(b.pname);
    while(h[int(b.pname[0])-65][key].pname!=(b.pname))
    {
        if(k > 50)
        {
            cout<<"Product not Available"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(b.pname[0])-65;
    j=key;
    if (flag==0)
    {
      cout<<"Stock Available: "<<h[i][j].quantity<<endl;
      cout<<"Enter Quantity:  ";
      cin>>b.quantity;
      b.price=h[i][j].price;
      b.netamount=b.price*b.quantity;
      if (b.quantity>h[i][j].quantity)
        cout<<"Order Declined! Not enough stock available!";
      else
      {
                cout<<"\nBillNo: "<<b.billid<<endl;
                cout<<"Customer Name: "<<b.custname<<endl;
                cout<<"Product Name: "<<b.pname<<endl;
                cout<<"Price: "<<b.price<<endl;
                cout<<"Quantity: "<<b.quantity<<endl;
                cout<<"NetAmount: "<<b.netamount<<endl;
                h[i][j].quantity=h[i][j].quantity-b.quantity;
                fwrite(&b,1,sizeof(struct bill),f1);
      }

    }
    fclose(f1);
}
void billbook()
{
    struct bill b;
    int i=0,j,k=0,key=0,flag=0;
    string product_name,cname;
    //ifstream f1;
    //f1.open("bill.dat",ios::in | ios::binary);
    FILE *f1;
    f1=fopen("bill.dat","rb");
    while(fread(&b,1,sizeof(struct bill),f1))
    {
        cout<<"\nBillNo: "<<b.billid<<endl;
                cout<<"Customer Name: "<<b.custname<<endl;
                cout<<"Product Name: "<<b.pname<<endl;
                cout<<"Price: "<<b.price<<endl;
                cout<<"Quantity: "<<b.quantity<<endl;
                cout<<"NetAmount: "<<b.netamount<<endl;

    }
    fclose(f1);
}
void reversebill()
{
    struct bill b;
    int billno;
    int i=0,j,k=0,key=0,flag=0,flag1=0;
    string product_name,cname;
    ifstream f1;
    cout<<"\nEnter Bill Id to be reversed: ";
    cin>>billno;
    f1.open("bill.dat",ios::in | ios::binary);
    while(f1.read((char *) & b,sizeof(b)))
    {
        if (b.billid==billno)
       {
          key=hashkey(product_name);
          b.pname=product_name;
          //cout<<key;
          while(h[int(product_name[0])-65][key].pname!=product_name)
          {
             if(k > 50)
             {
                cout<<"Product not Available"<<endl;
                flag=1;
                break;
             }
             key=(key+(k*k))%100;
             k++;
          }
          i=int(product_name[0])-65;
          j=key;
          if (flag==0)
          {
              h[i][j].quantity=h[i][j].quantity+b.quantity;
              cout<<"\nBill successfully Reversed";
          }
          flag1=1;
          break;
       }
    }
    if (flag1==0)
        cout<<"\nBill not found! ";
    f1.close();
}
void createproduct()
	{
		int product_number,product_quantity,shelf,row;
		int i=0,key=0,flag=0;
	    float  product_price;
	    string product_name;
		cout<<endl<<"Please Enter The Product Number: ";
		cin>>product_number;
		cout<<endl<<"Please Enter The Name of The Product: ";
		cin>>product_name;
		cout<<endl<<"Please Enter The Price of The Product: ";
		cin>>product_price;
		cout<<endl<<"Please Enter Total Quantity of The Product: ";
		cin>>product_quantity;
		cout<<endl<<"Please Enter Shelf Number: ";
		cin>>shelf;
		cout<<endl<<"Please Enter row Number";
		cin>>row;
		transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper);
		key=hashkey(product_name);
		cout<<key;
		while(h[int(product_name[0])-65][key].pno!='\0')
        {
            key=(key+(i*i))%100;
            if (i>500)
            {
                cout<<"no space available";
                break;
                flag=1;
            }
            i++;}
		if (flag==0)
        {h[int(product_name[0])-65][key]={product_number,product_name,product_price,product_quantity,shelf,row};
		cout<<key<<endl;
        }


}
void displayallproducts()
{
    int i,j;
    for(i=0;i<26;i++)
    {
        for(j=0;j<100;j++)
        {
            if(h[i][j].pno!='\0')
            {
                cout<<"product No:"<<h[i][j].pno<<endl;
                cout<<"Name: "<<h[i][j].pname<<endl;
                cout<<"Price: "<<h[i][j].price<<endl;
                cout<<"Quantity: "<<h[i][j].quantity<<endl;
                cout<<"shelfno: "<<h[i][j].shelfno<<endl;
                cout<<"Rowno: "<<h[i][j].rowno<<"\n"<<endl;
                cout<<"i,j"<<i<<" "<<j<<endl;
            }
        }
    }
}
void autocheckstock()
{
    int i,j;
    cout<<"The following items are short in stock!\n";
    cout<<"Please maintain stock as soon as possible!\n";
    for(i=0;i<26;i++)
    {
        for(j=0;j<100;j++)
        {
            if(h[i][j].pno!='\0' && h[i][j].quantity<5)
            {
                cout<<"product No:"<<h[i][j].pno<<endl;
                cout<<"Name: "<<h[i][j].pname<<endl;
                cout<<"Price: "<<h[i][j].price<<endl;
                cout<<"Quantity: "<<h[i][j].quantity<<endl;
                cout<<"shelfno: "<<h[i][j].shelfno<<endl;
                cout<<"Rowno: "<<h[i][j].rowno<<"\n"<<endl;
                cout<<"i,j"<<i<<" "<<j<<endl;
            }
        }
    }
}
void showproduct()
{
    int i=0,j,k=0;
    int flag=0,key=0;
    string product_name;
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>product_name;
    transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper);
    key=hashkey(product_name);
    cout<<key;
    while(h[int(product_name[0])-65][key].pname!=product_name)
    {
        if(k > 50)
        {
            cout<<"Product not found !"<<endl;
            cout<<"please Enter Correct Product Name"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(product_name[0])-65;
    j=key;
    if (flag==0)
    {
    cout<<"product No:"<<h[i][j].pno<<endl;
    cout<<"Name: "<<h[i][j].pname<<endl;
    cout<<"Price: "<<h[i][j].price<<endl;
    cout<<"Quantity: "<<h[i][j].quantity<<endl;
    cout<<"shelfno: "<<h[i][j].shelfno<<endl;
    cout<<"Rowno: "<<h[i][j].rowno<<endl;
    cout<<"i,j"<<i<<" "<<j<<endl;
    }
}
void checkstock()
{
    int i=0,j,k=0;
    int flag=0,key=0;
    string product_name;
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>product_name;
    transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper);
    key=hashkey(product_name);
    cout<<key;
    while(h[int(product_name[0])-65][key].pname!=product_name)
    {
        if(k > 50)
        {
            cout<<"Product not found !"<<endl;
            cout<<"please Enter Correct Product Name"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(product_name[0])-65;
    j=key;
    if (flag==0)
    {
    cout<<"product No:"<<h[i][j].pno<<endl;
    cout<<"Name: "<<h[i][j].pname<<endl;
    cout<<"STOCK AVAILABLE: "<<h[i][j].quantity<<endl;

    }
}
void productloc()
{
    int i=0,j,k=0;
    int flag=0,key=0;
    string product_name;
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>product_name;
    transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper);
    key=hashkey(product_name);
    cout<<key;
    while(h[int(product_name[0])-65][key].pname!=product_name)
    {
        if(k > 50)
        {
            cout<<"Product not found !"<<endl;
            cout<<"please Enter Correct Product Name"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(product_name[0])-65;
    j=key;
    if (flag==0)
    {

    cout<<"Name: "<<h[i][j].pname<<endl;
    cout<<"shelfno: "<<h[i][j].shelfno<<endl;
    cout<<"Rowno: "<<h[i][j].rowno<<endl;
    }
}
void modifyproduct()
{
    int i=0,j,k=0;
    int flag=0,key=0;
    string product_name;
    int product_number,product_quantity,shelf,row;
    float product_price;
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>product_name;
    transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper);
    key=hashkey(product_name);
    while(h[int(product_name[0])-65][key].pname.compare(product_name)!=0)
    {
        if(k>50)
        {
            cout<<"Product not Available !"<<endl;
            cout<<"please Enter Correct Product Name"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(product_name[0])-65;
    j=key;
    if (flag==0)
    {
        int c;
        cout<<"\n\tPress 1 to  CHANGE PRICE";
	    cout<<"\n\tPress 2 to UPDATE QUANTITY";
	    cout<<"\n\tPress 3 to UPDATE PRODUCT LOCATION\n";
	    product_number=h[i][j].pno;
	    product_name=h[i][j].pname;
        product_price=h[i][j].price;
        product_quantity=h[i][j].quantity;
        shelf=h[i][j].shelfno;
        row=h[i][j].rowno;
	    cin>>c;
        switch(c)
        {
        case 1:
            cout<<endl<<"Please Enter The New Price of The Product: ";
		    cin>>product_price;
		    break;
        case 2:
            cout<<endl<<"Please Enter updated Quantity of The Product: ";
		    cin>>product_quantity;
		    break;
        case 3:
            cout<<endl<<"Please Enter New Shelf Number: ";
		    cin>>shelf;
		    cout<<endl<<"Please Enter New row Number";
		    cin>>row;
		    break;
        default:
            cout<<"Wrong Input!"<<endl;
        }
        h[int(product_name[0])-65][key]={product_number,product_name,product_price,product_quantity,shelf,row};
    }
}
void removeproduct()
{
    int i=0,j,k=0;
    int flag=0,key=0;
    string product_name;
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>product_name;
    transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper);
    key=hashkey(product_name);
    cout<<key;
    while(h[int(product_name[0])-65][key].pname!=product_name)
    {
        if(k > 50)
        {
            cout<<"Product not found !"<<endl;
            cout<<"please Enter Correct Product Name"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(product_name[0])-65;
    j=key;
    if (flag==0)
    {
    cout<<"product No:"<<h[i][j].pno<<endl;
    h[i][j].pno='\0';
    }
}

int main()
{
    fflush(stdin);
    int i,j;
    for(i=0;i<26;i++)
    {
        for(j=0;j<100;j++)
        {
            h[i][j].pno='\0';
        }
    }
    //remove("product.dat");
    //FILE *fp;
    //fopen("temp.dat","wb");
    ifstream fp1;
    fp1.open("product.dat",ios::in | ios::binary);
    fp1.read((char *) & h,sizeof(h));
    displayallproducts();
    //fwrite(&h,1,sizeof(struct newproduct[26][100]),fp);
    //fclose(fp);
    //fp.write((char*)&h,sizeof(h));
    fp1.close();
    //showproduct();
    //modifyproduct();
    //removeproduct();
    generatebill();
    billbook();
    ofstream fp;
    fp.open("product.dat",ios::out | ios::binary);
    //fp.read((char*) &k,sizeof(k));
    //createproduct();
    //createproduct();
    //displayallproducts();
    fp.write((char *)& h,sizeof(h));
    delete [] &h;
    fp.close();

}


