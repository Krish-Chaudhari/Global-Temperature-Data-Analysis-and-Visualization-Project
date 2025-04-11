#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZ 256 

struct fileStruct{
// Define a structure to hold data from the file, including two new columns for year and month
    int  year;
	int month;
	//columns from the file
	char itemDate[20];
    float averageTemp;
    float averageTempU;
    float LandMaxTemperature;
    float LandMaxTemperatureU;
    float LandMinTemperature;
    float LandMinTemperatureU;
    float LandOceanAvgTemperature;
    float LandOceanAvgTemperatureU;
    
};


int main(void) 
{
// Define the maximum number of characters in one line as 256 to read line by line
    char alines[LSIZ];
       
    // Declare variables and arrays for various calculations and data storage

    int YearA[10000];
    float AverageYearlyTemperature[10000];
    float TotalTemp;
    char Curryr[5];
    int Startyear=1750;
    int Endyear=1759;
    int ActYear;
    int TmpYear;
    int currentyear1;
    int CountYear;
    int LineCountTemp;
    
	//declare variables for monthly average calculations	
    int monthTmp;
    float monthlyRunningAvgTmp[12];
    float monthlyAvgTmp[12];
    int monthYearCount;
    int monthYearMinIgnore=1899;
    
    //declare variables fo the hottest month calculations
    // Used for Question 3
    int MonthlyHottest=0;
    int Yearlyhot=0;
    float MaximumAverageTemperature=-100;
    int MonthColdest=0;
    int YearColdest=0;
    float AverageColdesrMonth=100;
    
	char Namef[30];
	FILE *hii = NULL; 
    int i = 0;
    int total = 0;
    
    char Year1[20];
    strcpy(Year1, "");
        
    float landAvgT;
       
    //set the file name
    strcpy(Namef, "GlobalTemperatures.csv");
    //open the file
    hii = fopen(Namef, "r");
    
    //initialize helping variables
    TotalTemp=0;
	LineCountTemp=0;
    CountYear=-1;
    currentyear1=1;
    *Curryr='\0';
    
    monthYearCount=0;
    i=-1; // set i to -1 as we will skip the first row, with the column titles
    
    //declare an array of fileStruct structure to hold read data from the file
    struct fileStruct fileData[10000];
    
    //The assumption is that the file data is ordered by the first column, date, ascending
    
    //read line by line from the file using fgets
g    while(fgets(alines, LSIZ, hii) != NULL)  
	{
		//make sure to add string termination character at the end of the read line
        alines[strlen(alines) - 1] = '\0'; 
        
        //skip the first line
        if(i>=0){ 
			 landAvgT=0;
			 
			 //use the sscanf function to parse the line into individual fields
			 sscanf(alines,"%[^,],%f,%f,%f,%f,%f,%f,%f,%f",fileData[i].itemDate,&fileData[i].averageTemp,&fileData[i].averageTempU,&fileData[i].LandMaxTemperature,&fileData[i].LandMaxTemperatureU,&fileData[i].LandMinTemperature,&fileData[i].LandMinTemperatureU,&fileData[i].LandOceanAvgTemperature,&fileData[i].LandOceanAvgTemperatureU);
			
			char tmpYear[5]="";
			char tmpMonth[3]="";
			*tmpYear = '\0';
			*tmpMonth='\0';
			
			//get currently processed year as a number
			strncpy(tmpYear,fileData[i].itemDate,4); 
			ActYear=atoi(tmpYear);
			TmpYear=ActYear;
			landAvgT=fileData[i].averageTemp;
			
			//get currently processed month as a number
			strncpy(tmpMonth,&fileData[i].itemDate[5],2); 
			monthTmp=atoi(tmpMonth); 
			
			//update year and the month in the structure
			fileData[i].year=TmpYear;
			fileData[i].month=monthTmp;
			
			//Question 4: get the hottest and coldest  month
				if(landAvgT >= MaximumAverageTemperature){
					MonthlyHottest=monthTmp;
					Yearlyhot=TmpYear;
					MaximumAverageTemperature=landAvgT;
				}
				
				if(landAvgT <= AverageColdesrMonth){
					MonthColdest=monthTmp;
					YearColdest=TmpYear;
					AverageColdesrMonth=landAvgT;
				}
			
			//Question 3: check if we are processin a year for which we are doing monthly average
			if (TmpYear > monthYearMinIgnore){
				if (currentyear1 != TmpYear)	{
					monthYearCount+=1;
				}
				monthlyRunningAvgTmp[monthTmp-1]+=landAvgT;
			}
			
			//for the calculation of average year temp it is only for years after yearMaxIgnore
			
			//Question 1, but used for other questions too
			if (ActYear > Endyear ){ 
				//is it a record with a new year
				if (currentyear1 != TmpYear)	{
					//ignore the average calculation for the first time, before the year gets set
					if(CountYear >= 0){

						AverageYearlyTemperature[CountYear]=TotalTemp/(LineCountTemp); 
						YearA[CountYear]=currentyear1;

						

						//reset running total and the counter
						TotalTemp=0;
						LineCountTemp=0; 
					}
					//increase the year count and set the 'new' current year
					CountYear+=1;
					currentyear1=TmpYear;   
				}
				
				//update running total and the number of items
				TotalTemp =TotalTemp + landAvgT;
				LineCountTemp++;
			}
		}
        i++;
		
		
    }
    
    //total number of the lines read from the file
    total=i-1;
    
    //Question 1 related: for the last items, there will not be switch of the year, so we need to process it now
    if(TotalTemp > 0){
		YearA[CountYear]=currentyear1; 
		AverageYearlyTemperature[CountYear]=TotalTemp/(LineCountTemp); 
	}
       
    //based on the monthly running data, get now the average monthly temperature
	for(int k = 0; k < 12; ++k){
		monthlyAvgTmp[k]=monthlyRunningAvgTmp[k]/monthYearCount; 
	}
	 
	//make sure to close the file
    fclose(hii); 
    
    //Question 2 variables
    int Century[10];
    float CenturyAverageTemperature[10];
    int CountCentury;
    int CenturyCurrent;
    int CenturyTemperature;
    float RunningtotalCentury;
    int CounttempRun;
	
	CenturyCurrent=0;
	CenturyTemperature=0;
	CountCentury=0;
	CounttempRun=0;

	//Question 4 variables
	int hottestAvgYear=0;
	float hottestAvgYearTemp=0;
	int coldestAvgYear=0;
	float coldestAvgYearTemp=100;

	//print the report of yearly average temperatures 
	//and at the same time find century averages, and the hotest and coldest year (Question 2 and 5)
	//const char *fill = "-----------------------------------------------"; 
	const char *fillHead = "*********************************************"; 
	
	//Question 1 report
	//Question 1: print the title and the header for yearly average temperature
	printf("%s%d%s\n", "Question 1: Yearly average temperature report from ",Endyear+1,":");  
	printf("%-15s%s\n", "Year","Avg Land Temp");  
	printf("%.*s\n", 28, fillHead);
	
	//Question 5, get the hottest and coldest yearly temperatures 
	for(i = 0; i <= CountYear; ++i)
    {
		//print yearly average 
        printf("%-15d%f\n", YearA[i],AverageYearlyTemperature[i]);    
        
        //to avoid running another loops, we are getting hottest and coldest avg temperatures data here
        if ( hottestAvgYearTemp <= AverageYearlyTemperature[i]){
			hottestAvgYearTemp=AverageYearlyTemperature[i];
			hottestAvgYear= YearA[i];
		}
		
		if ( coldestAvgYearTemp >= AverageYearlyTemperature[i] ){
			coldestAvgYearTemp= AverageYearlyTemperature[i];
			coldestAvgYear= YearA[i]; 
		}
		
        
        //Question 2, get the average by century
        //to avoid running another loops, we are getting data by century here
        CenturyTemperature=(YearA[i]/100)+1;
        if (CenturyTemperature != CenturyCurrent){
			if (CenturyCurrent > 0 ){
				CenturyAverageTemperature[CountCentury-1]=RunningtotalCentury/CounttempRun;
				Century[CountCentury-1]=CenturyCurrent; 
			}
			CountCentury+=1;
			CenturyCurrent=CenturyTemperature;
			RunningtotalCentury=0;
			CounttempRun=0;
		}
		RunningtotalCentury+=AverageYearlyTemperature[i];
		CounttempRun++;
    }
    
    //Question 2: if anyhthing left to process by century, do it now
    if(CounttempRun > 0){
		CenturyAverageTemperature[CountCentury-1]=RunningtotalCentury/CounttempRun;
		Century[CountCentury-1]=CenturyCurrent;
	}
    
	printf("\n");
    
    //Question 2 report
    //print title and header for Average century data
    printf("%s%d%s\n", "Question 2: Century average temperature report from ",Endyear + 1,":");  
    printf("%-15s%s\n", "Century","Avg Century Temp");
    //print average century data  
    for(i = 0; i < CountCentury; ++i)
    {
        printf("%-15d%f\n",Century[i], CenturyAverageTemperature[i]);   
        //printf("%.*s\n", 28, fill);   
    }
        
    printf("\n");
    
    //Question 3 report
    //print title and header for Average monthly data
    printf("%s%d%s\n", "Question 3: Monthly average temperature report from ",monthYearMinIgnore + 1,":");  
    printf("%-15s%s\n", "Month","Avg Month Temp");  
    //pring average monthly data
    for(i = 0; i < 12; ++i)
    {
        printf("%-15d%f\n",i+1, monthlyAvgTmp[i]);   
        //printf("%.*s\n", 28, fill);  
    }
    
    printf("\n");
	
	//Question 4 report
	//print details about the hottest recorded montlhy and yearly average temperatures
	printf("%s%d-%02d %s%f\n", "Question 4: The hottest recorded monthly average temperature was:",Yearlyhot,MonthlyHottest,"with the temperature: ",MaximumAverageTemperature);  
	printf("%s%d-%02d %s%f\n", "The coldest recorded monthly average temperature was:",YearColdest,MonthColdest,"with the temperature: ",AverageColdesrMonth);  

	printf("\n");
	
	//Question 5 report
	printf("%s%d %s%f\n", "Question 5:The hottest recorded yearly average temperature was:",hottestAvgYear ,"with the temperature: ",hottestAvgYearTemp);  
	printf("%s%d %s%f\n", "The coldest recorded yearly average temperature was:",coldestAvgYear ,"with the temperature: ",coldestAvgYearTemp);  
	
    printf("\n");

	float TemperatureMaxByYear[10000] = { 0 };
	float TemperatureMinByYear[10000]={0};
	float Tempocean[10000] = {0};
    // Iterate through the data and accumulate maximum temperatures for each year
    for (int j = 0; j <= total; ++j) {
        int currentYear = fileData[j].year;
        float maxTemp = fileData[j].LandMaxTemperature;
		float minTemp=fileData[j].LandMinTemperature;
		
        TemperatureMaxByYear[currentYear] += maxTemp;
		TemperatureMinByYear[currentYear]+=minTemp;
        float oceantemp = fileData[j].LandOceanAvgTemperature;
        Tempocean[currentYear] += oceantemp;
    }

	float maxTempAvgByYear[10000] = { 0 };
	float minTempAvgByYear[10000]={0};
	float Tempoceaanavg[10000] = {0};
    for (int j = 0; j <= CountYear; ++j) {
        
			
            maxTempAvgByYear[YearA[j]] = TemperatureMaxByYear[YearA[j]] / 12;
			minTempAvgByYear[YearA[j]]= TemperatureMinByYear[YearA[j]]/12;
			Tempoceaanavg[YearA[j]] = Tempocean[YearA[j]] / 12;
    }
	FILE *outputFile = fopen("maxTempAvgByYear.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(outputFile, "Year\tAverage Maximum Temperature\tAverage Minimum Temperature\tAverage Temperature\n");
    for (int j = 0; j <= CountYear; ++j) {
        fprintf(outputFile, "%d\t%.2f\t%.2f\t%.2f\n", YearA[j],AverageYearlyTemperature[j], maxTempAvgByYear[YearA[j]], minTempAvgByYear[YearA[j]]);
    }

    fclose(outputFile);
	FILE *GNUPlotData = fopen("Question_7Data.txt","w");

	// Combines the 19th and 20th century data into one file 
	float CombinedTemperatureData[1200][8];
	char CombinedDates[1200][11];

	// Calculates the land average temperatures for the 19th century
	for(int i = 41; i <= 140; i++){
		CombinedTemperatureData[i - 41][0] = AverageYearlyTemperature[i];

	}

	// Start Index for the 20th century is 141
	// End Index for the 20th century is 240
	for(int i = 141; i <= 240; i++){
		CombinedTemperatureData[i - 141][1] = AverageYearlyTemperature[i];

	}

	fprintf(GNUPlotData,"#Year 19th Century  20th Century\n");
	// Loops through all the merged data and reads it into a file 
	for(int i = 0; i < 100; i++){
		fprintf(GNUPlotData,"%d %f %f\n",i+1,CombinedTemperatureData[i][0],CombinedTemperatureData[i][1]);
	}

	fclose(GNUPlotData);
	 

    // Accumulate ocean temperatures for each year
    
   

    // Calculate the average ocean temperature for each year
    
    
    FILE *outpu = fopen("maxTempAvgByYear.txt", "w");
    if (outpu == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(outpu, "Year\tAverage Maximum Temperature\tAverage Ocean Temperature\n");
    for (int j = 0; j <= CountYear; ++j) {
        fprintf(outpu, "%d\t%.2f\t%.2f\n", YearA[j], AverageYearlyTemperature[j], Tempoceaanavg[j]);
    }

    fclose(outputFile);
    FILE *outp = fopen("GNUPlotData.txt", "w");
    if (outp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(outp, "# Century\tAverage Temperature\tLow Temperature\tHigh Temperature\n");

    int centuryStartYear = 1700;
    int centuryEndYear = 1799;
    float centuryAverageTemp = 0;
    float centuryLowTemp = 1000; // Initialize with a high value
    float centuryHighTemp = -1000; // Initialize with a low value
    int numYears = 0;

    for (i = 0; i < total; ++i) {
        int currentYear = fileData[i].year;
        if (currentYear >= centuryStartYear && currentYear <= centuryEndYear) {
            centuryAverageTemp += fileData[i].averageTemp;
            if (fileData[i].LandMinTemperature < centuryLowTemp) {
                centuryLowTemp = fileData[i].LandMinTemperature;
            }
            if (fileData[i].LandMaxTemperature > centuryHighTemp) {
                centuryHighTemp = fileData[i].LandMaxTemperature;
            }
            numYears++;
        } else {
            // Calculate averages for the current century
            if (numYears > 0) {
                centuryAverageTemp /= numYears;
                fprintf(outputFile, "%d\t%f\t%f\t%f\n", (centuryStartYear / 100) + 1,
                        centuryAverageTemp, centuryLowTemp, centuryHighTemp);
            }

            // Move to the next century
            centuryStartYear += 100;
            centuryEndYear += 100;
            centuryAverageTemp = 0;
            centuryLowTemp = 1000;
            centuryHighTemp = -1000;
            numYears = 0;

            // Process the current year again
            --i;
        }
    }

    // Calculate averages for the last century
    if (numYears > 0) {
        centuryAverageTemp /= numYears;
        fprintf(outp, "%d\t%f\t%f\t%f\n", (centuryStartYear / 100) + 1,
                centuryAverageTemp, centuryLowTemp, centuryHighTemp);
    }
	fclose(outp);

	
	float k[10000] = { 0 };
	float k1[10000] = { 0 };
	for (i = 0; i < total; ++i) {
        if (fileData[i].year >= 2000 && fileData[i].year <= 2015) {
			k[i]=fileData[i].averageTemp;
			k1[i]=fileData[i].averageTempU;
            
        }}
	float k3[12]={0};
	float k4[12]={0};
	for(int i=0;i<12;i++){
		for(int j=i;j<total;j+=12){
			k3[i]+=k[j];
			k4[i]+=k1[j];
		}
		k3[i] /= 15; 
        k4[i] /= 15;
	}


    
    FILE *outp1 = fopen("GNUPlotErrorBarData.txt", "w");
    if (outp1 == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(outp1, "# Month\tAverage Temperature\tUncertainty\n");

    for (i = 0; i < 12; ++i) {
    fprintf(outp1, "%f\t%f\n", k3[i], k4[i]);
}

    fclose(outp1);


	
    
   

    return 0;
}
