library(tidyverse)
library(dplyr)
library(ggplot2)
bankchurners <- read.csv("BankChurners.csv")
bankchurners %>%  
  select(Education_Level, Customer_Age, Income_Category, Credit_Limit) %>%
  #mutate(Education_Level = as.factor(Education_Level), Customer_Age = as.double(Customer_Age)) %>%
  
#Income_Category
  group_by(Income_Category) %>%
  summarise(count = n()) %>%
  ggplot(aes(Income_Category, count, fill = Income_Category)) +
  geom_col()

#numerical_2
  group_by(Credit_Limit) %>%
  ggplot(aes(x = Credit_Limit)) +
  geom_boxplot()
  
#numerical_2
  group_by(Credit_Limit) %>%
  ggplot(aes(Credit_Limit)) +
  geom_histogram(bins = 30)
  
  bankchurners %>%  
  summarise(Q1 = quantile(Credit_Limit, 0.25),
            mean = mean(Credit_Limit),
            median = median(Credit_Limit),
            Q3 = quantile(Credit_Limit, 0.75),
            IQR = IQR(Credit_Limit))

#categorical
  group_by(Education_Level) %>%
  summarise(count = n()) %>%
  ggplot() +
  geom_col(aes(Education_Level, count, fill = Education_Level))

#numerical
  group_by(Customer_Age) %>%
  ggplot(aes(Customer_Age)) +
  geom_histogram(bins = 30)
  
  bankchurners %>%
  summarise(Q1 = quantile(Customer_Age, 0.25),
            mean = mean(Customer_Age),
            median = median(Customer_Age),
            IQR = IQR(Customer_Age))