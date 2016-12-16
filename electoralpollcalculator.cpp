#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;


bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
    "KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC."
    "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}


bool hasCorrectSyntax(string pollData) // to check whether the poll string is legit or not
{
    for (int i = 0; i != pollData.size(); i++)
    {
        if (!isdigit(pollData[i]) && !isalpha (pollData[i])) // for loop to check whether the string contains special characters or not
        {
            return false;
        }    
    }
    int k = 0;      
    
    while (k < pollData.size())     
    {
        
        
        string stateCode = pollData.substr(k, 2); //builds a substring of the kth and (k+1)th character of the pollstring
        for (int z = 0; z <2; z++)
        {
            stateCode[z] = toupper(stateCode[z]);
        }
        if (!isValidUppercaseStateCode(stateCode))     
            return false;
        
        if (isalpha(pollData[k]) == true && isalpha(pollData[k+1]) == true)
        {
            if (isdigit(pollData[k+2]) == true && isdigit(pollData[k+3]) == false)
            {
                k = k + 4; // increments the character position by 4
            }
            else if (isdigit(pollData[k+2]) == true && isdigit(pollData[k+3]) == true)
                
                k = k + 5; // increments the character position by 5
            else 
                return true;
        }
    }
    
    return true;
}

int countVotes(string pollData, char party, int& voteCount) // counts the total number of votes of the particular party in question
{
    if (!hasCorrectSyntax(pollData))  //calls on the boolean function to crosscheck whether the pollstring is legit
        return 1;
    else
    {
        for (int j = 0; j != pollData.size(); j++)
        {
            if( (pollData[j] == '0' && isalpha(j-1) && isalpha(j+1)) || (pollData[j] == '0' && pollData[j+1] == '0'))
            {
                return 2;
            }
            
        }
        
        if(!isalpha(party))
            return 3;
        
        voteCount = 0; // initializing the vote count of the party entered by the user as 0
        
        
        for (int i = 0; i != pollData.size(); i++)
        {
            if ((toupper(pollData[i]) == toupper(party)) || (tolower(pollData[i] == tolower(party))))
            {
                if (isdigit(pollData[i-1]) && isdigit(pollData[i-2]))
                {
                    char c0='0';
                    int m=c0;
                    int c = pollData[i-1] - m; // to convert the ASCII character to an integer
                    int c1 = pollData[i-2] - m;
                    voteCount = voteCount + 10*c1 + c; // adds the integer voteCount to get the required number of votes for the iser entered party
                }
                
                else if (isdigit(pollData[i-1]) && !isdigit(pollData[i-2]))
                {
                    char c0='0';
                    int m=c0;
                    int c = pollData[i-1] - m;
                    voteCount = voteCount + c;
                    
                }
                
            }}
    }
    return 0;
}


int main()
{
    if (hasCorrectSyntax("TX38RCA55D"))
        cout << "Passed test 1: hasCorrectSyntax(\"TX38RCA55D\")" << endl;
    if (!hasCorrectSyntax("MX38RCA55D"))
        cout << "Passed test 2: !hasCorrectSyntax(\"MX38RCA55D\")" << endl;
    int votes;
    votes = -999;    // so we can detect whether countVotes sets votes
    if (countVotes("TX38RCA55DMs6rnY29dUT06L", 'd', votes) == 0  &&  votes == 84)
        cout << "Passed test 3: countVotes(\"TX38RCA55DMs6rnY29dUT06L\", 'd', votes)" << endl;
    votes = -999;    // so we can detect whether countVotes sets votes
    if (countVotes("TX38RCA55D", '%', votes) == 3  &&  votes == -999)
        cout << "Passed test 4: countVotes(\"TX38RCA55D\", '%', votes)" << endl;
    return 0;
}
