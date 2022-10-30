library(tidyverse)
library(dplyr)
library(ggplot2)
library(corrplot)
demand <- read.csv("demandRename.csv")
demand %>%
  
  #correlation matrix
  corrplot(cor(demand), method = 'number')

  #linear regression
  model1 <- lm(Non.urgent ~ TypeB, demand)
  summary(model1)

  model2 <- lm(Non.urgent ~ TypeB + TypeC, demand)
  summary(model2)

  model3 <- lm(Non.urgent ~ TypeB + TypeC + Target.total, demand)
  summary(model3)
  
  model4 <- lm(Non.urgent ~ TypeB + Target.total, demand)
  summary(model4)