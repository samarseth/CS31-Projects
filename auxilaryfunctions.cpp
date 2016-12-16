#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;
int appendToAll(string a[], int n, string value) // to add a string "value" to the end of each string of  the array 
{
    if (n<0) // return -1 if the integer n is negative
        return -1;
    for (int i = 0; i<n; i++)
    {
        a[i] = "" + a[i] + value; // appends value to the end of the string
    }
    return n;
}
int lookup(const string a[], int n, string target) // to find the position of the integer that is equal to target
{
    
    if (n<0)
    {
        return -1;
    }
    for (int i =0; i < n; i ++)
    {
        if (a[i] == target)
        {
            return i; // prints i if the ith position of the array is qual to target  
        }
    }
    return -1; // if none of the above cases apply, return -1
}
int positionOfMax(const string a[], int n) // finds the position of the string which is greater than all other integers
{
    if (n<=0)
        return -1; // accounts for the trivial case when n is negative
    for (int i = 0; i < n ; i++)
    {
        int m = 0; 
        for (int k =0; k<n; k++)
        {
            if (a[i] >= a[k])
                m = 2; 
            else 
            {
                m = 3;
                break; // breaks the for-loop if the string is not the greatest
            }
        }        
        if(m == 2)
        {
            return i; // returns the position of the greatest string
        }
        
    }
    return -1; // return -1 if none of the above test cases apply
}
int rotateLeft(string a[], int n, int pos)
{
    if ( n == 0 && pos == 0)
        return 0;
    if (n<0 || pos > n-1|| pos<0)
        return -1; // accounts for the trivial case when n is negative
    
    string temp;
    temp = a[pos];
    for (int i = pos; i < n-1; i++)
    {
        a[i] = a[i+1]; // checks whether i and i+1 are equal 
    }
    a[n-1] = temp;
    
    if (pos < 0 && pos > n)
    {
        return -1; //trivial case when either pos is negative or greater than n 
    }
    return pos; 
}
int countRuns(const string a[], int n)
{
    if (n<0)
        return -1; //trivial case when n is negative
    int count = 0;
    for (int i = 0; i <n;  i++)
    {
        if (a[i] != a[i+1]) 
        {
            count++; // adds to count 
        }
    }
    return count; //prints count
}

int flip(string a[], int n) // reverses the sequence of strings in an array
{
    if (n<0)
    {
        return -1; // returns -1 when n is negative
    }
    
    for(int k=0; k!=(n/2); k++)
    {
        string temp=a[k];  // assigns the ith string of 'a' to a new string, temp
        a[k]=a[n-1-k];
        a[n-1-k]=temp;
    }
    
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if( n1 < 0 || n2 <0)
        return -1; // accounts for the trivial case when either n1 or n2 is negative
    int n; // decalre a new integer n
    if (n1>n2)
        n = n2; // assigns n2 to n 
    else
        n = n1; // assigns n1 to n
    for (int i = 0; i<n; i++)
    {
        if ( a1[i] != a2[i]) 
        {
            return i; // returns i if the corresponding strings of the array are not equal to each other
        }
    }
    return n;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2<0 || n2>n1)
        return -1;
    if ( n1==0 && n2==0)
        return 0;
    
    for (int i =0; i < n1; i++)
    {
        int m=0;
        if (a2[0] == a1[i])
        {
            
            for (int j = 0; j <n2; j++)
            {
                if (a2[m] == a1[i+m])
                    m++;
            }
        }
        if (m == n2)
            return i;
    }
    return -1;
}
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if ( n1 < 0|| n2< 0)
        return -1; // tests the trivial case either of n1 or n2 are negative or not
    
    for (int i = 0 ; i < n1; i++)
    {
        for (int j =0; j < n2; j++) 
        {
            if (a1[i] == a2[j])
                return i; // returns i when both a[i] and a[j] are equal
        }
    }
    return -1;
}


int separate(string a[], int n, string separator) // seprates strings lower than the separator form those greater than it
{
    if(n<0)
        return -1; // accounts for the trivial case when 
    int counter=0;
    for(int p=0; p<n; p++){
        if(a[p]<separator){
            counter++;
            string temp; // define a temporary string variable, temp
            temp=a[p];
            for(int k=p; k>0; k--){
                a[k]=a[k-1];
            }
            a[0]=temp; // assigns temp to the 0th string of array a
        }
        for(int j=0; j<n; j++){
            if(a[p]==separator){
                string same;
                same=a[p];
                for(int i=p; i>counter; i--){
                    a[i] = a[i-1];
                }
                a[counter]=separator;
            }
        }
    }
    if(counter==0){   //if all the elements are greater than the separator then return n
        return 0;
    }
    return counter;
}
int main()
{
    string h[7] = { "jill", "hillary", "donald", "tim", "", "evan", "gary" };
    assert(lookup(h, 7, "evan") == 5);
    assert(lookup(h, 7, "donald") == 2);
    assert(lookup(h, 2, "donald") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "jill", "hillary", "gary", "mindy" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "jill?" && g[3] == "mindy?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "gary?" && g[3] == "hillary?");
    
    string e[4] = { "donald", "tim", "", "evan" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string d[5] = { "hillary", "hillary", "hillary", "tim", "tim" };
    assert(countRuns(d, 5) == 2);
    
    string f[3] = { "gary", "donald", "mike" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "gary");
    
    assert(separate(h, 7, "gary") == 3);
    
    cout << "All tests succeeded" << endl;
    
}
