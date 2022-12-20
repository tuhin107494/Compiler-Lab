#include<bits/stdc++.h>
#define pb push_back
using namespace std;
int num_of_productions,sz=0;
vector< string>production_set[20];
set<string>nter;
void add_to_Result_Set(vector<string> &Result, string val)
{
    int k;
    for (k = 0; k<Result.size(); ++k)
    {
        if (Result[k] == val)
        {
            return;
        }
    }
    Result.pb(val);
}

void FIRST(vector<string> &Result, string c)
{
   // cout << c << endl;
    int i, j, k;
    vector<string >Sub_Result;
    int found_epsilon;
    if (nter.find(c)==nter.end())
    {
        //cout << "Paisi "<<c<<endl;

        add_to_Result_Set(Result, c);
        return;
    }

    for (i = 0; i < sz; ++i)
    {
        if (production_set[i][0] == c)
        {
            if (production_set[i][2] == "#")
                add_to_Result_Set(Result, "$");
            else
            {
                j = 2;

                while (j<production_set[i].size())
                {
                    found_epsilon = 1;

                    FIRST(Sub_Result, production_set[i][j]);

                    for (k = 0; k <Sub_Result.size(); ++k)
                        add_to_Result_Set(Result, Sub_Result[k]);

                    for (k = 0; k < Sub_Result.size(); ++k)
                        if (Sub_Result[k] == "$")
                        {
                            found_epsilon = 0;
                            break;
                        }
                    if (found_epsilon)
                        break;
                    j++;
                }
            }
        }
    }
    return;
}
int main()
{
    int i;
    char choice;
    vector<string>result;
    printf("Enter the no. of productions : ");
    cin>>num_of_productions;
    puts("Enter the production string like \"E=E+T\" \nand epsilon as #");
    cin.ignore();
    for (int j= 0; j < num_of_productions; ++j,sz++)
    {
        printf("Enter production Number %d : ", j+ 1);

        string s,temp;
        getline(cin,s);
        string ss;
        ss+=s[0];
        nter.insert(ss);
        production_set[sz].pb(ss);
        production_set[sz].pb("=");

        for(int i=2; i<s.size(); i++)
        {


            if(isspace(s[i]))
            {

                production_set[sz].pb(temp);
                temp="";

            }
            else if(s[i]=='/')
            {

                production_set[sz].pb(temp);

                temp="";

                ss="";
                ss+=s[0];
                nter.insert(ss);
                ++sz;
                production_set[sz].pb(ss);
                production_set[sz].pb("=");
            }
            else temp+=s[i];

        }

        production_set[sz].pb(temp);

        for(int i=0; i<sz; i++)
        {
           // for(int m=0; m<production_set[i].size(); m++)cout<<production_set[i][m]<<" ";
            //cout<<endl;
        }

    }
   // set<string>::iterator it;
 //   for(it = nter.begin(); it!=nter.end(); it++) cout << *it << ' ';
    //cout << endl;
    do
    {
        printf("Find FIRST of --> ");
        string c;
        cin>>c;
        FIRST(result, c);
        cout<<"\nFirst ("<<c<<") = {";
        for(i=0; i<result.size(); i++)
        {
            cout << result[i];
            i+1 == result.size() ? cout << "}\n" : cout << ",";
        }
        result.clear();

        printf("Press \'y\' or \'Y\' to continue : ");
        cin>>choice;
    }
    while (choice == 'y' || choice == 'Y');
    return 0;
}


