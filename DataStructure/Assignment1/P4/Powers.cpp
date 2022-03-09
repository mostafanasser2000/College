#include<iostream>


using namespace std;

long long Power(int a, int n){
	if(n == 0){
		return 1;
	}
	else{
		return a * Power(a,n-1);
	}
	
}
long long Power_2(int a, int n){
    // handle when power is odd
	if(n % 2 != 0){
		return a * Power(a,(n/2)) * Power(a,(n/2));
	}
	else{
		return Power(a,n/2) * Power(a,n/2); 
	}
	
	
}


int main(){
	
int a,n;
cout<<"Enter the number and power"<<endl;
cin>>a>>n;
long long ans1 = Power(a,n);
long long ans2 = Power_2(a,n);
cout<<ans1<<endl;
cout<<ans2<<endl;
	
	
	
}
