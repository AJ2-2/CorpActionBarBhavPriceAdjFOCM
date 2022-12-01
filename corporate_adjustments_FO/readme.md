
Notes to apply corp action to CM data


1. Get two files from tejas : 

	Note : format of these files is important, make sure that format matches the previous files or else cpp code will break.

		1.1 Corporate Adjustment Factors.csv
		
			- here they have frequently changed the format of date so take that into factor with new file.
			- you can convert date format externally or adjust the date in cpp code ( i have adjusted date in cpp code)
		
		1.2 NSE Symbol Changes.csv
		
			- here important thing to note is this file should be sorted on date because a symbol can have multiple name change
			 	command used : sort -t, -k4 NSE_Symbol_Changes.csv

2. I have made 2 cpp code to adjust minutely and bhav data seperately, make compile these accordinly.

3. To process data in batch, use scripts
	3.1 run_bhav.sh to process bhav_data and adjust it with new factors and symbol name change.
	3.2 run_minutely.sh to process minutely_data and adjust it with factors and symbol name change.


4. In FO, date format is different for years 2018,2019,2020,2021
	therefore changed the logic of code so that corp factors to adjust minutely data can work without fixing the date format first

