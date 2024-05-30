#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 8 14:44:33 2023
Based on: https://www.kaggle.com/datasets/arbazmohammad/world-airports-and-airlines-datasets
Sample input: --AIRLINES="airlines.yaml" --AIRPORTS="airports.yaml" --ROUTES="routes.yaml" --QUESTION="q1" --GRAPH_TYPE="bar"
@author: rivera
@author: mayaa
"""
import pandas as pd
import sys
import yaml 
from matplotlib import pyplot as plt

def split_args() -> list:
    """Function that reads user input from stdin and modifies it into usable program data
        Parameters
        ----------
            input : None
                Will read from the command line, rather than a passed parameter.
        Returns
        -------
            list[str]
                A lsit containing the 5 expected values that were written in the command line
    
    
    """

    result = []
    Airline_arg:str = sys.argv[1]
    Airports_arg:str = sys.argv[2]
    Routes_arg:str = sys.argv[3]
    Question_arg:str = sys.argv[4]
    Graph_Type_arg:str = sys.argv[5]


    #Split up the args, to get the filenames and values
    Airline_arg = Airline_arg.split("=")
    Airline_File = Airline_arg[1]
    result.append(Airline_File)

    Airports_arg = Airports_arg.split("=")
    Airports_File = Airports_arg[1]
    result.append(Airports_File)

    Routes_arg= Routes_arg.split("=")
    Routes_File = Routes_arg[1]
    result.append(Routes_File)

    Question_arg = Question_arg.split("=")
    Question = Question_arg[1]
    result.append(Question)

    Graph_Type_arg = Graph_Type_arg.split("=")
    Graph_Type = Graph_Type_arg[1]
    result.append(Graph_Type)
    #Return the final Array containing all the Data Values
    return result

def get_answer(airlines:pd.DataFrame, airports:pd.DataFrame, routes:pd.DataFrame, question:str) -> pd.DataFrame:
    """Function to sort the DataFrames depending on which question is being asked.
            Parameters
            ----------
                airlines: pd.DataFrame, airports: pd.DataFrame , routes : pd.DataFrame, question : str, required
                    The DataFrames containing the information and the question that is being asked.

            Returns
            -------
                pd.DataFrame
                    The answer to the provided question within a Pandas DataFrame.
    """

    
    #Determine which question is being asked
    if(question == "q1"): #TOP 20 AIRLINES WITH MOST CANADIAN ROUTES

        airlines.drop(["airline_country"], inplace=True, axis=1)
        airports.drop(["airport_name", "airport_city", "airport_icao_unique_code", "airport_altitude"], inplace=True, axis=1)
        routes.drop(["route_from_aiport_id"], inplace=True, axis=1)
        
        #Change routes info so it can be merged easily
        df1: pd.DataFrame = routes.rename(columns={'route_airline_id':'airline_id', 'route_to_airport_id':'airport_id'})

        #Merge dataframes and sort only Canadian Destinations
        merged_df: pd.DataFrame = pd.merge(airports, df1, on="airport_id", how="left").dropna()
        merged_df: pd.DataFrame = merged_df[merged_df['airport_country']=="Canada"]

        #Finalize the DataFrame to be written to the .csv file
        results: pd.DataFrame = pd.merge(merged_df, airlines, on="airline_id", how="left")
        results["airline_name"] = results['airline_name'].astype(str) +" ("+ results["airline_icao_unique_code"] + ")"

        answer: pd.DataFrame = results.groupby(['airline_name'],as_index=False).size().sort_values(by=['size', 'airline_name'], ascending=(False,True)).head(20)
        answer: pd.DataFrame = answer.rename(columns={'airline_name': 'subject', 'size': 'statistic' })
        
        return answer
        
    elif(question == "q2"): #30 LEAST POPULAR DESTINATION COUNTRIES

        #Drop columns that are not needed
        airports.drop(['airport_name', 'airport_city', 'airport_icao_unique_code', 'airport_altitude'], inplace=True, axis=1)
        routes.drop(['route_airline_id', 'route_from_aiport_id'], inplace=True, axis=1)

        #Rename and Merge DataFrames
        routes: pd.DataFrame = routes.rename(columns={'route_to_airport_id': 'airport_id'})
        airports['airport_country'] = airports['airport_country'].str.lstrip()

        merge: pd.DataFrame = pd.merge(routes, airports, on='airport_id', how="left")
        

        
        #Format Answer Dataframe
        answer: pd.DataFrame = merge.groupby('airport_country', as_index=False).size().sort_values(by=['size', 'airport_country'], ascending=True).head(30)
        answer: pd.DataFrame = answer.rename(columns={'airport_country': 'subject', 'size': 'statistic' })

        return answer

        
    elif(question == "q3"): #TOP 10 DESTINATION AIRPORTS

        #Drop columns that are not needed
        airports.drop(["airport_altitude"], inplace=True, axis=1)
        routes.drop(["route_from_aiport_id", "route_airline_id"], inplace=True, axis=1)

        #Rename columns and Merge DataFrames
        routes: pd.DataFrame = routes.rename(columns={"route_to_airport_id": "airport_id"})

        merge: pd.DataFrame = pd.merge(routes, airports, on=["airport_id"], how="left")
        merge['airport_name'] = merge['airport_name'] + " (" + merge['airport_icao_unique_code'] + "), " + merge['airport_city'] +", " + merge['airport_country']

        #Format DataFrame to be turned into a csv file
        answer: pd.DataFrame = merge.groupby('airport_name', as_index=False).size().sort_values(by=['size', 'airport_name'], ascending=(False, True)).head(10)
        answer: pd.DataFrame = answer.rename(columns={'airport_name': 'subject', 'size': 'statistic' })
        
        return answer

    elif(question == "q4"): #TOP 10 DESTINATION CITIES

        #Drop columns that are not needed
        
        airports.drop(["airport_name", "airport_icao_unique_code", "airport_altitude"], inplace=True, axis=1)
        routes.drop(["route_from_aiport_id", "route_airline_id"], inplace=True, axis=1)

        #Rename and Merge

        routes: pd.DataFrame = routes.rename(columns={"route_to_airport_id": "airport_id"})
        merge: pd.DataFrame = pd.merge(routes, airports, on=["airport_id"], how="left")

        #Format DataFrame to go into csv file
        merge["airport_city"] = merge['airport_city'] +", "+ merge["airport_country"]
        
        answer: pd.DataFrame = merge.groupby('airport_city', as_index=False).size().sort_values(by=['size', 'airport_city'], ascending=(False, True)).head(10)
        answer: pd.DataFrame = answer.rename(columns={'airport_city': 'subject', 'size': 'statistic' })
    
        return answer
    else: #UNIQUE TOP 10 CANADIAN ROUTES WITH MOST DIFFERENCE BETWEEN DEST ALTITUDE AND ORIGIN ALTITUDE
        airlines.drop(["airline_name", 'airline_icao_unique_code'], inplace=True, axis=1)
        airports.drop(["airport_name","airport_city"], inplace=True, axis=1)
        
        #Sort out only Canadian Routes
        airports: pd.DataFrame = airports[airports['airport_country']=='Canada']
        airlines: pd.DataFrame = airlines[airlines['airline_country']=='Canada']

        #Rename Columns to be sorted more easily
        route_info: pd.DataFrame = routes.rename(columns={"route_from_aiport_id": "origin_id", "route_to_airport_id": "dest_id", "route_airline_id": "airline_id"})
        origin_airports: pd.DataFrame = airports.rename(columns={'airport_id':'origin_id', 'airport_icao_unique_code': 'origin_code', 'airport_altitude': 'origin_alt'})
        dest_airports: pd.DataFrame = airports.rename(columns={'airport_id':'dest_id', 'airport_icao_unique_code':'dest_code', 'airport_altitude': 'dest_alt'})

        #Drop columns that are not needed
        base:pd.DataFrame = pd.merge(route_info, airlines, on="airline_id", how="left").dropna()
        base.drop(['airline_id', 'airline_country' ], inplace=True, axis=1)

        merge: pd.DataFrame = pd.merge(base, origin_airports, on="origin_id").dropna()
        merge.drop(['airport_country', 'origin_id'],inplace=True, axis=1)

        #Format Data for sorting
        final: pd.DataFrame = pd.merge(merge, dest_airports, on='dest_id', how='left').dropna()
        final['dest_alt'] = abs(final['dest_alt'].astype(float) - final['origin_alt'].astype(float))
        final['origin_code'] = final['origin_code'] + "-" + final['dest_code']

        final.drop(['airport_country', 'dest_id', 'origin_alt', 'dest_code'], inplace=True, axis=1)
    
        
        answer: pd.DataFrame= final.groupby(['origin_code', 'dest_alt'], as_index=False).size().sort_values(by=['dest_alt', 'size'], ascending=False).head(10)
        answer.drop(['size'], inplace=True, axis=1)
        answer['dest_alt'] = answer['dest_alt']

        #Format for csv File
        answer = answer.rename(columns={'origin_code': 'subject', 'dest_alt': 'statistic' })
        
        return answer

    
def create_dataframe(filename:str) -> pd.DataFrame:
    """Function to take the name of a yaml file as input and return the organized file contents within a Pandas DataFrame
            Parameters
            ----------
                filename : str, required
                    The yaml file to be read and turned into a DataFrame.

            Returns
            -------
                pd.DataFrame
                    The contents of the file in a pandas DataFrame.
    """
    
    
    #Open the file and load values into DataFrame
    with open(filename) as f:
        data =yaml.load(f)
        key = list(data.keys())
        vals = data.get(key[0])
        answer = pd.DataFrame(vals)

    return answer
    
def create_graph_and_csv(result:pd.DataFrame, question:str, graph_type:str):
    """Function to create the required output depending on which question was asked
            Parameters
            ----------
                result: pd.DataFrame, question : str, graph_type : str, required
                    The DataFrame containing the answer, the question that was asked, and the type of graph to be generated.

            Returns
            -------
                None
                    This function does not return anything.
    """

    
    filename_csv:str = question + ".csv"
    filename_pdf:str = question + ".pdf"

    #Create CSV File
    result.to_csv(filename_csv, index=False)

#Create Graph depending on question, and whether or not the graph_type is 'bar' or 'pie
    if (question == "q1"):
        result:pd.DataFrame = result.rename(columns={'subject': 'Airlines', 'statistic': 'Number of Routes'})
        if(graph_type == "bar"):
            

            ax = result.plot(x='Airlines', y='Number of Routes', kind="barh", figsize=(10,7))
            plt.title('Airlines with most Routes to Canada')
            plt.tight_layout()
            plt.subplots_adjust(bottom=0.15)

            plt.savefig(filename_pdf, format="pdf")
        else:

            ax = result.plot.pie(subplots = True, y='Number of Routes', figsize=(16,9))
            
            plt.title('Airlines with most Routes to Canada')
            plt.tight_layout()

            labels = list(result['Airlines'])
            plt.legend(labels, loc="best")
            plt.savefig(filename_pdf, format="pdf")

    elif (question == "q2"):
        result: pd.DataFrame = result.rename(columns={'subject': 'Countries', 'statistic': 'Number of Appearances'})
        if(graph_type == "bar"):
            ax = result.plot(x='Countries', y='Number of Appearances', kind="barh", figsize=(10,6))
            plt.title('Least Popular Destination Countries')
            plt.subplots_adjust(bottom=0.15)
            plt.tight_layout()

            plt.savefig(filename_pdf, format="pdf")  
        else:
            ax = result.plot.pie(subplots = True, y='Number of Appearances', figsize=(16,9))
            
            plt.title('Least Popular Destination Countries')
            plt.tight_layout()

            labels = list(result['Countries'])
            plt.legend(labels, loc="best")
            plt.savefig(filename_pdf, format="pdf")
    elif (question == "q3"):
        result: pd.DataFrame = result.rename(columns={'subject': 'Airports', 'statistic': 'Number of Appearances'})
        if(graph_type == "bar"):
            ax = result.plot(x='Airports', y='Number of Appearances', kind="barh", figsize=(10,6))
            plt.title('Most Popular Destination Airports')
            plt.subplots_adjust(bottom=0.15)
            plt.tight_layout()

            plt.savefig(filename_pdf, format="pdf")  
        else:
            ax = result.plot.pie(subplots = True, y='Number of Appearances', figsize=(16,9))
            
            plt.title('Most Popular Destination Airports')
            plt.tight_layout()

            labels = list(result['Airports'])
            plt.legend(labels, loc="best")
            plt.savefig(filename_pdf, format="pdf")
    elif (question == "q4"):
        result: pd.DataFrame = result.rename(columns={'subject': 'Cities', 'statistic': 'Number of Appearances'})
        if(graph_type == "bar"):
            ax = result.plot(x='Cities', y='Number of Appearances', kind="barh", figsize=(10,6))
            plt.title('Most Popular Destination Cities')
            plt.subplots_adjust(bottom=0.15)
            plt.tight_layout()

            plt.savefig(filename_pdf, format="pdf")  
        else:
            ax = result.plot.pie(subplots = True, y='Number of Appearances', figsize=(16,9))
            
            plt.title('Most Popular Destination Cities')
            plt.tight_layout()

            labels = list(result['Cities'])
            plt.legend(labels, loc="best")
            plt.savefig(filename_pdf, format="pdf")
    else:
        result: pd.DataFrame = result.rename(columns={'subject': 'Routes', 'statistic': 'Difference in Altitude'})
        if(graph_type == "bar"):
            ax = result.plot(x='Routes', y='Difference in Altitude', kind="barh", figsize=(10,6))
            plt.title('Top Canadian Routes with the Greatest Difference in Altitude from Origin to Destination')
            plt.subplots_adjust(bottom=0.15)
            plt.tight_layout()

            plt.savefig(filename_pdf, format="pdf")  
        else:
            labels = list(result['Difference in Altitude'])
            ax = result.plot.pie(subplots=True, labels=labels, y='Difference in Altitude', figsize=(16,9))
            
            plt.title('Top Canadian Routes with the Greatest Difference in Altitude from Origin to Destination')
            plt.tight_layout()

            labels = list(result['Routes'])
            plt.legend(labels, loc="best")
            plt.savefig(filename_pdf, format="pdf")


def main():
    """Main entry point of the program.

    This function will take the parameters provided by the user from the Command Line, and create a csv file and a graph to answer whichever question was asked.
    
    """
    
    
    #Sort arguments into a list
    args = split_args()

    airlines = args[0]
    airports = args[1]
    routes = args[2]
    question = args[3]
    graph_type = args[4]
    
    
    #Put Files into Dataframes
    airlines_df = create_dataframe(airlines) #Create Dataframe from airlines.yaml
    airports_df = create_dataframe(airports) #Create Dataframe from airports.yaml
    routes_df = create_dataframe(routes) #Create Dataframe from routes.yaml

    
    answer = get_answer(airlines_df, airports_df, routes_df, question) #Get the answer and store in a dataframe

    create_graph_and_csv(answer, question, graph_type) #Generate output 




if __name__ == '__main__':
    main()
