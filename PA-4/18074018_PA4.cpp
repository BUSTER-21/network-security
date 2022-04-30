#include<bits/stdc++.h>
#define ll   long long int
#define fast    ios_base::sync_with_stdio(false);cin.tie(0);
#define r0      return 0
#define all(c)  c.begin(),c.end()
#define sz(r)   r.size()


// Function to generate random numbers
void multiplicativeCongruentialMethod(int Xo, int m, int a,vector<int>& randomNums,int noOfRandomNums)
{
    // Initialize the seed state
    randomNums[0] = Xo;
 
    // Traverse to generate required numbers of random numbers
    for (int i = 1; i < noOfRandomNums; i++) 
    {
     // Follow the multiplicative congruential method
        randomNums[i] = (randomNums[i - 1] * a) % m;
    }
}

void linearCongruentialMethod(int Xo, int m, int a, int c,vector<int>& randomNums,int noOfRandomNums)
{
 // Initialize the seed state
    randomNums[0] = Xo;
 
    // Traverse to generate required numbers of random numbers
    for (int i = 1; i < noOfRandomNums; i++) 
    {
        // Follow the linear congruential method
        randomNums[i] = ((randomNums[i - 1] * a) + c) % m;
    }
}

double runsTest(vector<int>& randomNums, int l_median)
{
  
    int runs=0;
    int n1=0;
    int n2=0;
    int f=0;
      
     // Checking for start of new run
    for(int i=0;i<sz(randomNums);i++)
    {
       // no. of runs
        if(randomNums[i] >= l_median)
        {
            n1++;
            if(f == 0)
            {
                runs += 1;  
                f= 1;
            }
        }
        if(randomNums[i] < l_median)
        {
            n2++;
            if(f == 1 || (f == 0 && i ==0))
            {
                runs++;
                f = 0;
            }
        }
    }
    
    cout<<'\n'<<"runs: "<<runs<<'\n';
    cout<<"n1 : "<<n1<<"  n2 : "<<n2;
    double runs_exp = double((2*n1*n2)/double(n1+n2))+1;

    cout<<'\n'<<"runs_exp: "<<runs_exp;

    double stan_dev = sqrt((2*n1*n2*(2*n1*n2-n1-n2))/ (((n1+n2)*(n1+n2))*(n1+n2-1)));
  
    cout<<'\n'<<"stdev: "<<stan_dev;

    double z = (runs-runs_exp)/stan_dev;
  
    return z;

}
  
int main() 
{ 
    fast;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int Xo = 10087; // seed value
    int m = 226; // modulus parameter
    int a = 3; // multiplier term

 
    // Number of Random numbers to be generated
    int noOfRandomNums = 100;
 
    // To store random numbers
    vector<int> randomNums(noOfRandomNums);
     
    int f,t;
    // f=0 for multiplicative otherwise linear method. 
    // t==1 for runs test of randomness .
    cin>>f>>t;
    
    if(f==0)
    {
        multiplicativeCongruentialMethod(Xo, m, a, randomNums, noOfRandomNums);
    }
    else
    {
        int c = 3; // Increment term
        linearCongruentialMethod( Xo, m, a, c, randomNums, noOfRandomNums);
    }
 
    // Print the generated random numbers
    for (int i = 0; i < noOfRandomNums; i++)
    {
        cout << randomNums[i] << " ";
    }
    
    //test 1
    // test1(runs test of randomness);
    if(t==1)
   {
    size_t n = randomNums.size() / 2;
    nth_element(randomNums.begin(), randomNums.begin()+n, randomNums.end());
   
     // Making a list of 100 random numbers 
    
    int l_median= randomNums[n];
  
    double Z = abs(runsTest(randomNums, l_median));
  
    cout<<'\n'<<"median: "<<l_median;
    cout<<'\n'<<"Test_1 Z-statistic= "<< Z;
   }
   //test 2 Monte Carlo method
   else
   {
      // values = [5,125,10,1,32, 101,33, 54,200,230,215,93,50,100,3,6,43]
      ll mx=*max_element(all(randomNums));
      double inval=0.0;
      double outval=0.0;
      ll ptr=0;

      cout<<'\n'<<"First Five Pairs:"<<'\n';
      cout<<"\t\tX \t\tY \t\tZ:";


     for(auto i=0;i<sz(randomNums)/2;i++)
     {
       double x = double(randomNums[ptr]-mx/2)/double(mx/2);
       double y = double(randomNums[ptr+1]-mx/2)/double(mx/2);

      double z = sqrt(x*x+y*y);
      if (i<5.0)
        cout<<'\n'<<'\t'<<x<<'\t'<<y<<'\t'<<z<<'\n';
          // cout<<"\t"<<round(x,3)<<"\t"<<round(y,3)<<"\t"<<round(z,3);
      if (z<1.0)
        inval=inval+1;
      else
        outval=outval+1;
      
      ptr=ptr+2;
    }

    cout<<"\nInval:"<<inval<<" Outval:"<< outval;

    cout<<"\nResult: "<<4.0*inval/(inval+outval);

    r0; 
  }
}

