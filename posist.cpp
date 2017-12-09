#include<bits/stdc++.h>
using namespace std;

struct Node{
    string data;
    string password;
    int NodeNumber;
    int NodeId;
    mutable const struct Node* ReferenceNodeId;
    mutable int ChildNodeId;
    mutable const struct Node* ReferenceChildNodeId;

    bool operator < (const Node &other) const { return NodeId < other.NodeId; }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DATA AND PASSWORD ENCRYPTION
// USED THE DES TECHNIQUE only 1 layer for encryption

//CODE FOR DATA ENCRYPTION

map<int,string> passwordkeys;
map<int,string> datakeys;

string encryption(string str,int NodeId,int ch)
{
    string encr="";
    string key="";
    string input=str;
    //cout<<"\n"<<input;
    string binary="";
    //cout<<endl;
    for(size_t i=0;i<input.size();i++)
    {
    bitset<8> b(input.c_str()[i]);
    binary+= b.to_string();
    }

    //cout<<"Binary code: "<<binary<<endl<<endl;
    int len=binary.length();
    string left="",right="";
    left=binary.substr(0,len/2);
    right=binary.substr(len/2,len/2);

    char temp=right[0];
    key=right.substr(1,len/2-1)+temp;
    char enc[10000];
    memset(&enc[0], 0, sizeof(enc));
    for(int i=0;i<len/2;i++)
    {
    enc[i]=left[i]^(right[i]^key[i]);
    }
    encr=enc+left;
    //cout<<"Encrypted code : "<<encr<<endl<<endl;

    if(ch==1)
        datakeys[NodeId]=key;
    else
        {
           // cout<<"\ninsdf\n";
            //cout<<NodeId<<"\n";
            passwordkeys[NodeId]=key;
            //cout<<"les"<<passwordkeys[NodeId];
        }
    //cout<<"\nencrypted "<<encr<<"\n";
    return encr;
    /*string data1 = encr;
    stringstream sstream(data1);
    string output1;
    while(sstream.good())
    {
    bitset<8> bits;

    sstream >> bits;
    char c = char(bits.to_ulong());
    output1 += c;
    }

    cout<<"Encrypted string: "<<output1<<endl<<endl;*/

}

int decryption(string str,int NodeId,string password,int p)
{
    //cout<<str<<NodeId<<password;
    string encr=str;
    string left="";
    string right="";
    string key=passwordkeys[NodeId];
    //cout<<"yo"<<key<<"\n";
    int len=encr.length();
    left=encr.substr(0,len/2);
    right=encr.substr(len/2,len/2);
    char enc1[10000];
    memset(&enc1[0], 0, sizeof(enc1));
    for(int i=0;i<len/2;i++)
    {
    enc1[i]=right[i]^(left[i]^key[i]);
    }
    string decr=right+enc1;
    //cout<<"Decrypted code : "<<decr<<endl<<endl;

    string data = decr;
    stringstream sstream1(data);
    string output;
    while(sstream1.good())
    {

    bitset<8> bits;
    sstream1 >> bits;
    char c = char(bits.to_ulong());
    output += c;
    }
    if(p==1)
    {cout<<"After Decyption password "<<output<<"\n\n";
    size_t found = output.find(password);
    if (found!=std::string::npos)
    {
        return 1;
    }
    else
        return 0;
    }
    else
    {
        cout<<"the data of the owner is\n";
        cout<<output<<"\n\n";
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


vector< set<Node> > mset;
int numberofsets=1;
int currentnodeid=1;

void createfirstnode()
{

    //hard coding the first node
    set<Node> temp;
    Node head;
    head.password="12345678";
	head.ReferenceNodeId= NULL;
	head.data="vivek negi 8826404733 IIIT-Delhi boys hostel";
	head.NodeNumber=1;
	head.NodeId=currentnodeid++;
	head.ChildNodeId=-1;
	head.ReferenceChildNodeId=NULL;
	//encrypting the data and password
	head.password=encryption(head.password,head.NodeId,2);
	head.data=encryption(head.data,head.NodeId,1);
    temp.insert(head);
    mset.push_back(temp);
}

void createmultifirstnode()
{

    cout<<"how many sets of first nodes do you want to create?\n";
    int n;
    cin>>n;
    cin.ignore(1,'\n');

    numberofsets=n;
    for(int i=0;i<n;i++)
    {
        cout<<"first node of other set\n";
        set<Node> temp;
        Node head;
        head.ReferenceNodeId= NULL;
        cout<<"type in something to be stored as data\n";
        getline(cin,head.data);
        cout<<"type new password\n";
        getline(cin,head.password);
        head.NodeNumber=i;
        head.NodeId=currentnodeid++;
        head.ChildNodeId=-1;
        head.ReferenceChildNodeId=NULL;
        head.password=encryption(head.password,head.NodeId,2);
        head.data=encryption(head.data,head.NodeId,1);

        temp.insert(head);
        mset.push_back(temp);
    }
}

void addnode()
{
    cout<<"to which set you want to add the node\n";
    cout<<"select number from 0 to "<<numberofsets-1<<"\n";
    int n;
    cin>>n;
    cin.ignore(1,'\n');
    Node temp;
    cout<<"type something to be inserted into data\n";
    getline(cin,temp.data);
    cout<<"type new password!\n";
    getline(cin,temp.password);
    //cout<<temp.password;

    temp.ChildNodeId=-1;
    temp.NodeId=currentnodeid++;
    temp.NodeNumber=n;
    temp.password=encryption(temp.password,temp.NodeId,2);
    temp.data=encryption(temp.data,temp.NodeId,1);
    temp.ReferenceChildNodeId=NULL;
    set<Node>:: iterator it=mset[n].end();
    it--;
    (*it).ChildNodeId=temp.NodeId;

    temp.ReferenceNodeId=&(*it);
    mset[n].insert(temp);
    set<Node>:: iterator it2=mset[n].end();
    it2--;
    (*it).ReferenceChildNodeId=&(*it2);
}

void displayallsets()
{
    for(int i=0;i<mset.size();i++)
    {
        cout<<"ALL NODES IN NODENUMBER "<<i<<"\n";
        for(set<Node>:: iterator it =mset[i].begin(); it != mset[i].end();++it)
        {

            cout<<"data "<<(*it).data<<"\n";
            cout<<"password "<<(*it).password<<"\n";
            cout<<"NodeId "<<(*it).NodeId<<"\n";
            cout<<"referenceNodeId "<<(*it).ReferenceNodeId<<"\n";
            cout<<"self referenceId "<<&(*it)<<"\n";
            cout<<"referenceChildNodeId "<<(*it).ReferenceChildNodeId<<"\n";
            cout<<"childnodeid "<<(*it).ChildNodeId<<"\n";
            cout<<"NodeNumber "<<(*it).NodeNumber<<"\n\n";

            //const Node *ptr=&(*it);
            //cout<<ptr;
        }
    }
}
int dnodeid;
int verifyowner()
{
    set<Node>:: iterator it;
    int NodeId;
    string password="";
    cout<<"enter the node id which you want to access\n";
    cin>>NodeId;
    dnodeid=NodeId;
    cin.ignore(1,'\n');
    int flag=0;
    for(int i=0;i<mset.size();i++)
    {
        for(it =mset[i].begin(); it != mset[i].end();++it)
        {
            if((*it).NodeId==NodeId)
            {
                flag=1;
                break;
            }
        }
    }
    if(flag==0)
    {
        cout<<"there is no node with this id\n";
        return 0;
    }
    cout<<"enter the password of your node\n";
    getline(cin,password);

    string key=passwordkeys[NodeId];
    int result=decryption((*it).password,NodeId,password,1);
    if(result==1)
    {
        cout<<"owner is verified\n";
        decryption((*it).data,NodeId,"",0);
    }
    else
        cout<<"wrong password\n";
    return result;
}


void mergenode()
{
    int n1,n2;
    cout<<"enter the two node numbers which you want to merge\n";
    cin>>n1>>n2;
    int size1,size2;
    size1=mset[n1].size();
    size2=mset[n2].size();
    if(size1>=size2)
    {
        mset[n1].insert(mset[n2].begin(), mset[n2].end());
        mset[n2].erase(mset[n2].begin(),mset[n2].end());
    }
    else
    {
        mset[n2].insert(mset[n1].begin(), mset[n1].end());
        mset[n1].erase(mset[n1].begin(),mset[n1].end());
    }
}

void longestchain()
{
    int max1=0;
    int longestnodenumber=0;
    for(int i=0;i<mset.size();i++)
    {
        if(mset[i].size()>max1)
        {
            longestnodenumber=i;
            max1=mset[i].size();
        }
    }
    cout<<"the longest node number is "<<longestnodenumber;
    cout<<"\nits size is "<<max1<<"\n";
}

void deletenode()
{
    set<Node>:: iterator it;
    int result=verifyowner();

    int flag=0;
    if(result==1)
    {
        for(int i=0;i<mset.size();i++)
        {
            for(it =mset[i].begin(); it != mset[i].end()&&flag==0;++it)
            {
                if((*it).NodeId==dnodeid)
                {
                    mset[i].erase(*it);
                    delete &it;
                    passwordkeys.erase(dnodeid);
                    datakeys.erase(dnodeid);
                    cout<<"NODE DELETED\n\n";
                    flag=1;
                    break;
                }
            }
        }
    }
}

int main()
{
    cout<<"choose the option 1 or 2\n";
    cout<<"1. create only one node with hardcoding\n";
    cout<<"2. create multi set of first node\n";
    int ch;
    cin>>ch;
    cin.ignore(1,'\n');
    if(ch==1)
    {
        createfirstnode();
    }
    else if(ch==2)
    {
        createmultifirstnode();
    }
    else{
        cout<<"incorrect input\n";
        return 0;
    }


    while(true)
    {
        int n;
        cout<<"choose the option\n";
        cout<<"1. add node to a set\n";
        cout<<"2. display all sets\n";
        cout<<"3. Verify the owner of the Node\n";
        cout<<"4. merge two node\n";
        cout<<"5. Find the longest chain of the main node\n";
        cout<<"6. delete node by verification of owner\n";
        cout<<"9. exit program\n";
        cin>>n;
        cin.ignore(1,'\n');
        if(n==1)
            addnode();
        else if(n==2)
            displayallsets();
        else if(n==3)
            verifyowner();
        else if (n==4)
            mergenode();
        else if(n==5)
            longestchain();
        else if(n==6)
            deletenode();
        else if(n==9)
            break;
        else
            "wrong input";
    }
    return 0;
}
