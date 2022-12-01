#include<bits/stdc++.h>
using namespace std;

unordered_map<string,vector<vector<string>>> corp_map;
set<string> corpDataMissingSet;

void load_corp_adj_file(string location)
{
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
			}
		}
	}
}

void load_ticker_name_change_list_file_sorted_by_date(string location)
{
//	cout<<"Loading ticker update list \n";
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
			
			if(corp_map.find(v[1])!=corp_map.end())
			{
				corp_map[v[2]]=corp_map[v[1]];
			//	cout<<"Loaded :"<<v[2]<<" ->"<<v[1]<<std::endl;
			}
		}
	}
}

void adjusted_action_data(vector<string> &v,int date)
{
	double adjustment_factor=1;

	if(v[0]!="FUTSTK") return;											// currently only adjusting FUT bhav data.

	if(corp_map.find(v[1])==corp_map.end()) corpDataMissingSet.insert(v[1]);
	else
	{
		int idx=0;
		while(idx<corp_map[v[1]].size())
		{
			int d1 = stoi(corp_map[v[1]][idx][0]);
			int d2 = stoi(corp_map[v[1]][idx][1]);

			if(date>=d1 && date<d2) break;
			else idx++;
		}
		if(idx==corp_map[v[1]].size()) corpDataMissingSet.insert(v[1]+" -> "+v[2]);
		else adjustment_factor=stod(corp_map[v[1]][idx][2]);
		
		double d = stod(v[5]);
		d*=adjustment_factor;
		v[5]=to_string(d);

		d = stod(v[6]);
		d*=adjustment_factor;
		v[6]=to_string(d);

		d = stod(v[7]);
		d*=adjustment_factor;
		v[7]=to_string(d);

		d = stod(v[8]);
		d*=adjustment_factor;
		v[8]=to_string(d);

		d = stod(v[9]);
		d*=adjustment_factor;
		v[9]=to_string(d);
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

	int date=stoi(x.substr(0,x.length()-4));

	int no_of_csv_fields = 15;
	
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

			if(idx==no_of_csv_fields+1)
			{
				if(v[1]=="SYMBOL") {outfile<<v[0]<<","<<v[1]<<","<<v[2]<<","<<v[3]<<","<<v[4]<<","<<v[5]<<","<<v[6]<<","<<v[7]<<","<<v[8]<<","<<v[9]<<","<<v[10]<<","<<v[11]<<","<<v[12]<<","<<v[13]<<","<<v[14]<<endl;continue;} 
				adjusted_action_data(v,date);					// skipping header!
				outfile<<std::fixed<<std::setprecision(2)<<v[0]<<","<<v[1]<<","<<v[2]<<","<<v[3]<<","<<v[4]<<","<<stod(v[5])<<","<<stod(v[6])<<","<<stod(v[7])<<","<<stod(v[8])<<","<<stod(v[9])<<","<<v[10]<<","<<v[11]<<","<<v[12]<<","<<v[13]<<","<<v[14]<<endl;
			}
		}
	}

//	cout<<"Corp data not found list :\n";
//	for(auto str:corpDataMissingSet)
//		cout<<str<<" ";
//	cout<<endl;

	return 0;
}
