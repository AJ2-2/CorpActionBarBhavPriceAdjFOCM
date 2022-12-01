#include<bits/stdc++.h>
using namespace std;

unordered_map<string,vector<vector<string>>> corp_map;
//ofstream corpDataNotFoundFile;
set<string> corpDataMissingSet;
int DATE;

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

			if(idx==5 && v[4].substr(0,2)=="FO")
			{
				vector<string> t;t.push_back(v[1].substr(0,4)+v[1].substr(5,2)+v[1].substr(8,2));t.push_back(v[2].substr(0,4)+v[2].substr(5,2)+v[2].substr(8,2));t.push_back(v[3]);
				
				//vector<string> t;
				//t.push_back(v[1].substr(6)+v[1].substr(3,2)+v[1].substr(0,2));
				//t.push_back(v[2].substr(6)+v[2].substr(3,2)+v[2].substr(0,2));
				//t.push_back(v[3]);
			
				corp_map[v[0].substr(4)].push_back(t);

				//cout<<"corp map:"<<v[0].substr(4)+"_EQ"<<endl;
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

			if(corp_map.find(v[1])!=corp_map.end())
			{
				corp_map[v[2]]=corp_map[v[1]];
		//		cout<<"Loaded : "<<v[2]<< -> "<<v[1]<<std::endl;
			}
		}
	}
}

void adjusted_action_data(vector<string> &v)
{
	double adjustment_factor=1;

	if(v[0].back()=='E') return;											// currently marketData DB only has adjutment factor for spot(FUT only) and EQ.

	int pos = v[0].find('_');
	if(pos>=v[0].length())
	{
		cout<<v[0]<<" check error\n";
		exit(1);
	}
	string _symbol = v[0].substr(0,pos);

	if(corp_map.find(_symbol)==corp_map.end()) corpDataMissingSet.insert(_symbol);
	else
	{
		int idx=0;
		while(idx<corp_map[_symbol].size())
		{
			int d1 = stoi(corp_map[_symbol][idx][0]);
			int d2 = stoi(corp_map[_symbol][idx][1]);

			if(DATE>=d1 && DATE<d2) break;
			else idx++;
		}
		if(idx==corp_map[_symbol].size()) corpDataMissingSet.insert(_symbol+" -> "+v[1]);
		else adjustment_factor=stod(corp_map[_symbol][idx][2]);
		
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
	
	DATE = stoi(x.substr(3,8));

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
