#include<bits/stdc++.h>
using namespace std;


class Node{
    public:
        string data;
        int h;
        int g;
        Node* next[100];
        unordered_map<Node*, int> k ;

        Node(){
            data="";
            h=0;
            g=0;
            k[NULL]=0;
            for(int i=0;i<100;i++){
                next[i]=NULL;
            }
        }
};

class Tree{
    private:
        Node* root;
    public:
        Tree(){
            root = new Node();   
        }
        int stringtoInt(string s){
            int bien =((s[0]-'0')*10+s[1])%100;
            return bien;
        }
        void Insert(string cha, int dgcha, string con, int dgcon, int kc){
            int x= stringtoInt(con);
            Node* Nodecon = new Node();
            if(root->data==""){
                root->data=cha;
                root->h=dgcha;
                Nodecon->data=con;
                Nodecon->h=dgcon;
                root->next[x]=Nodecon;
                Nodecon->k[root]=kc;
            }else{
                queue<Node*> DSL;
                Node* Nodecha = new Node();
                DSL.push(root);
                while(!DSL.empty()){
                    Node * tmp = DSL.front();
                    DSL.pop();
                    if(tmp->data==cha){
                        Nodecha = tmp;
                    }
                    if(tmp->data==con){
                        Nodecon = tmp;
                    }
                    for(int i=0;i<100;i++){
                        if(tmp->next[i]!=NULL){
                            DSL.push(tmp->next[i]);
                        }
                    }
                }
                if(Nodecon->data==""){
                    Nodecon->data=con;
                    Nodecon->h= dgcon;
                }
                if(Nodecha!=NULL){
                    Nodecha->next[x]=Nodecon;
                    Nodecon->k[Nodecha]=kc;
                }

            }
        }

        void Asao(string st, string en){
            ofstream outputFile("Output3.txt");
            outputFile<<"TT |  TTK |  k(u,v) |  h(v) |  g(v)  |   f(v)  |  Danh Sach L"<<endl;
            map<int, Node*> DSL;
            unordered_map<Node*, Node*> parent;
            int check = 0;
            DSL[root->h]=root;
            parent[root]=NULL;
            while(!DSL.empty()){
                Node * tmp = DSL.begin()->second;
                outputFile<<tmp->data<<"  |      |        |         |       |         |";
                if(tmp->data==st){
                    check =1;
                }
                if(tmp->data==en && check==1){
                    stack<string> path;
                    int qd=0;
                    Node* current = tmp;
                    while (current != nullptr) {
                        path.push(current->data);
                        qd += current->k[parent[current]];
                        current = parent[current];
                    }
                    outputFile << "\nDuong di la: ";
                    while (!path.empty()) {
                        outputFile << path.top() << " ";
                        path.pop();
                    }
                    outputFile<<"\nDo dai quang duong: "<<qd;
                    cout<<"Perfect.";
                    return;
                }
                DSL.erase(DSL.begin());
                for(int i=0;i<100;i++){
                    if(tmp->next[i]!=NULL){
                        if(check==1){
                            (tmp->next[i]->g) = (tmp->g) + (tmp->next[i] -> k[tmp]);
                            outputFile<<"\n   |  "<<tmp->next[i]->data<<"   |   "<<tmp->next[i]->k[tmp]<<"    |    "<<tmp->next[i]->h<<"   |   "<<tmp->next[i]->g<<"   |   "<<(tmp->next[i]->h)+(tmp->next[i]->g)<<"    |";
                            parent[tmp->next[i]]=tmp;
                        }
                        DSL[(tmp->next[i]->h)+(tmp->next[i]->g)] = tmp->next[i];
                    }
                }
                for (auto const& pair : DSL) {
                    outputFile<<pair.second->data<<pair.first  <<" ";
                }
                outputFile<<endl;
                outputFile<<"-----------------------------------------------------------------"<<endl;
            }
            cout<<"Du lieu bi sai, vui long kiem tra lai input";
        }
        void NhanhvaCan(string st, string en){
            stack<Node*> DSL;
            unordered_map<Node*,Node*> parent;
            int check =0;
            DSL.push(root);
            parent[root]=NULL;
            while (!DSL.empty())
            {
                Node* tmp = DSL.top();
                DSL.pop();
                if(tmp->data==st){
                    check=1;
                }
                if(tmp->data==en && check==1 && (DSL.top()->g+DSL.top()->h)>(tmp->g+tmp->h)){
                    stack<string> path;
                    int qd=0;
                    Node* current = tmp;
                    while (current != nullptr) {
                        path.push(current->data);
                        qd += current->k[parent[current]];
                        current = parent[current];
                    }
                    cout << "Duong di la: ";
                    while (!path.empty()) {
                        cout << path.top() << " ";
                        path.pop();
                    }
                    cout<<"\nDo dai quang duong: "<<qd;
                    return;
                }
                map<int, Node*> dstt;
                for(int i=0;i<100;i++){
                    if(tmp->next[i]!=NULL){
                        if(check==1){
                            (tmp->next[i]->g) = (tmp->g) + (tmp->next[i] -> k[tmp]);
                            parent[tmp->next[i]]=tmp;
                        }
                        dstt[(tmp->next[i]->h)+(tmp->next[i]->g)] = tmp->next[i];
                    }
                }
                while (!dstt.empty())
                {
                    DSL.push(dstt.rbegin()->second);
                    dstt.erase(dstt.rbegin()->first);
                }
                
                
            }
            
        }


}tree;


int main(){
    ifstream file("Input3.txt");
    string line;
    int n;
    string st, end;
    unordered_map<string, int> Dinh;
    //Bo dong 1
    getline(file, line);
    //Doc dong yeu cau
    getline(file, line);
    stringstream s1(line);
    s1 >> st >> end;
    getline(file, line);
    //Doc so dinh de lap
    getline(file, line);
    stringstream ss(line);
    ss>>n;
    getline(file, line);
    int count = 0;
    while (count < n && getline(file, line)) {
        stringstream ss(line);
        string dinh;
        int dg;
        if (ss >> dinh >> dg) {
            Dinh[dinh]=dg;
            count++;
        }
    }
    getline(file, line);
    bool check = false;
    string cha, con;
    int dgcha, dgcon, kc;
    while (getline(file, line)) {
        stringstream ss(line);
        if (ss >> cha >> con >> kc) {
            if (Dinh.count(cha) && Dinh.count(con)) {
            tree.Insert(cha, Dinh[cha], con, Dinh[con], kc);
            } else {
                cout<<"Du lieu bi sai, vui long kiem tra lai input";
                check = true;
                break;
            }
        }
    }

    file.close();
    if(!check){
        tree.Asao(st, end);
    }

    return 0;
}