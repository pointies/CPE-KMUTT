library(tidyverse)
library(dplyr)
library(ggplot2)
library(corrplot)
bankchurners <- read.csv("BankChurners.csv")
bankchurners %>%
  
#Gender-CardCategory
  select(Gender, Card_Category) %>%
  group_by(Gender, Card_Category) %>%
  ggplot(aes(Card_Category, fill = Gender)) + 
  geom_bar(position = "fill")
  chisq.test(table(bankchurners$Gender, bankchurners$Card_Category))

#Gender-Attrition_Flag
  select(Gender, Attrition_Flag) %>%
  group_by(Gender, Attrition_Flag) %>%
  ggplot(aes(Attrition_Flag, fill = Gender)) + 
  geom_bar(position = "fill")
  table(bankchurners$Gender, bankchurners$Attrition_Flag)
  
#Cross-Tabulation
  select(Attrition_Flag, Months_Inactive_12_mon) %>%
  group_by(Attrition_Flag, Months_Inactive_12_mon) %>%
  ggplot(aes(Months_Inactive_12_mon, fill = Attrition_Flag)) + 
  geom_bar(position = "fill")
  table(bankchurners$Attrition_Flag, bankchurners$Months_Inactive_12_mon)
  
#Correlation
  select(Months_on_book, Total_Relationship_Count, Months_Inactive_12_mon, Contacts_Count_12_mon,
         Credit_Limit, Total_Revolving_Bal, Avg_Open_To_Buy, Total_Amt_Chng_Q4_Q1, 
         Total_Trans_Amt, Total_Trans_Ct, Total_Ct_Chng_Q4_Q1, Avg_Utilization_Ratio)
  #cor(bankchurners$mpg,bankchurners$wt) # direct
  res <- cor(bankchurners) # pairwise
  corrplot(res, 
           type = "upper",
           order = "hclust",
           tl.col = "black",
           tl.srt = 45)