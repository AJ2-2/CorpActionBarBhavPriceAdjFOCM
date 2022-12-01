#include<bits/stdc++.h>
using namespace std;

unordered_map<string,vector<vector<string>>> corp_map;
//ofstream corpDataNotFoundFile;
set<string> corpDataMissingSet;

void load_corp_adj_file(string location)
{
//	cout<<"pushin in corp map though file:"<<location<<endl;

	ifstream f;f.open(location);
	vector<string> v(100);
	int idx;

	if(f.is_open())
	{
		string str;
		while(getline(f,str))
		{
			stringstream ss(str);
			idx=0;
			
			while(ss.good())
			{
				getline(ss,str,',');
				v[idx++]=str;
			}

			if(idx==5 && v[4].substr(0,2)=="EQ")
			{
				//vector<string> t;t.push_back(v[1].substr(0,4)+v[1].substr(5,2)+v[1].substr(8,2));t.push_back(v[2].substr(0,4)+v[2].substr(5,2)+v[2].substr(8,2));t.push_back(v[3]);
				vector<string> t;
				t.push_back(v[1].substr(6)+v[1].substr(3,2)+v[1].substr(0,2));
				t.push_back(v[2].substr(6)+v[2].substr(3,2)+v[2].substr(0,2));
				t.push_back(v[3]);
				corp_map[v[0].substr(4)+"_EQ"].push_back(t);
				corp_map[v[0].substr(4)+"_BE"].push_back(t);

			//	cout<<"corp map:"<<v[0].substr(4)+"_EQ"<<" and"<<v[0].substr(4)+"_BE"<<endl;
			}
		}
	}
}

void load_ticker_name_change_list_file_sorted_by_date(string location)
{
	//cout<<"Loading ticker update list \n";
	ifstream f;f.open(location);
	vector<string> v(100);
	int idx;

	if(f.is_open())
	{
		string str;
		while(getline(f,str))
		{
			stringstream ss(str);
			idx=0;
			while(ss.good())
			{
				getline(ss,str,',');
				v[idx++]=str;
			}

		//	cout<<"Checking :"<<v[1]<<" "<<v[2]<<std::endl;

			if(corp_map.find(v[1]+"_EQ")!=corp_map.end())
			{
				corp_map[v[2]+"_EQ"]=corp_map[v[1]+"_EQ"];
		//		cout<<"Loaded : "<<v[2]<<"_EQ -> "<<v[1]<<"_EQ"<<std::endl;
			}
			if(corp_map.find(v[1]+"_BE")!=corp_map.end())
			{
				corp_map[v[2]+"_BE"]=corp_map[v[1]+"_BE"];
		//		cout<<"Loaded : "<<v[2]<<"_BE -> "<<v[1]<<"_BE"<<std::endl;
			}

		}
	}
}

void adjusted_action_data(vector<string> &v)
{
	double adjustment_factor=1;

	if(corp_map.find(v[0])==corp_map.end()) corpDataMissingSet.insert(v[0]);
	else
	{
		int idx=0;
		while(idx<corp_map[v[0]].size())
		{
			int d1 = stoi(corp_map[v[0]][idx][0]);
			int d2 = stoi(corp_map[v[0]][idx][1]);

			if(stoi(v[1])>=d1 && stoi(v[1])<d2) break;
			else idx++;
		}
		if(idx==corp_map[v[0]].size()) corpDataMissingSet.insert(v[0]+" -> "+v[1]);
		else adjustment_factor=stod(corp_map[v[0]][idx][2]);
		
		double d = stod(v[3]);
		d*=adjustment_factor;
		v[3]=to_string(d);

		d = stod(v[4]);
		d*=adjustment_factor;
		v[4]=to_string(d);

		d = stod(v[5]);
		d*=adjustment_factor;
		v[5]=to_string(d);

		d = stod(v[6]);
		d*=adjustment_factor;
		v[6]=to_string(d);
	}
}

int main(int argc,char *argv[])
{
	string s=argv[3];
	string infileName = argv[1];
	infileName += s;
	ifstream f;f.open(infileName);

	load_corp_adj_file(argv[4]);
	load_ticker_name_change_list_file_sorted_by_date(argv[5]);

	string x=argv[3];	
	string outfileName = argv[2];
	outfileName += x;
	ofstream outfile;outfile.open(outfileName);	
	
    vector<string> v(100);
    int idx;
  
	if(f.is_open())
    {
		string str;
		while(getline(f,str))
		{
			stringstream ss(str);
			idx=0;
			while(ss.good())
			{
				getline(ss,str,',');
				v[idx++]=str;
			}

			if(idx>=8)
			{
				adjusted_action_data(v);
				for(int i=0;i<idx-1;i++)
				{
					if(i>=3 && i<=6) outfile<<stoi(v[i])<<",";
					else outfile<<v[i]<<",";
				}
				outfile<<v[idx-1]<<endl;

				//outfile<<v[0]<<","<<v[1]<<","<<v[2]<<","<<stoi(v[3])<<","<<stoi(v[4])<<","<<stoi(v[5])<<","<<stoi(v[6])<<","<<v[7]<<","<<v[8]<<endl;
			}
		}
	}

	//corpDataNotFoundFile.open("coprDataNotFoundFile.txt");
	
	//cout<<"Corp data not found list :\n";
	//for(auto str:corpDataMissingSet)
	//	cout<<str<<" ";
	//cout<<endl;

	return 0;
}
