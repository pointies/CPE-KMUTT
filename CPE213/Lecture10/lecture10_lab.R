library(tidyverse)
library(dplyr)
library(ggplot2)
library(caret)
library(e1071)
credit <- read.csv("credit-approval.csv")
credit
  
  colnames(credit) <- c("A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10", "A11", "A12", "A13", "A14", "A15", "A16") 

  #split_data
  n <- nrow(credit)
  train_id <- sample(1: n, size = 0.7 * n)
  train_data <- credit[train_id,]
  test_data <- credit[-train_id,]
  table(credit$A16)
  (306)/(306+383)
  
  #model
  model1 <- glm(as.factor(A16) ~ as.factor(A6) + as.factor(A9), data = train_data, family = binomial)
  summary(model1)
  res <- predict(model1,train_data, type='response')
  res_c <- factor(ifelse(res>0.45,'+','-'))
  res_c 
  confusionMatrix(res_c, as.factor(train_data$A16), positive='+', mode='prec_recall')
  
  #mode2
  model2 <- glm(as.factor(A16) ~ as.factor(A6) + as.factor(A9) + as.factor(A10) + as.factor(A13), data = train_data, family = binomial)
  summary(model2)
  res <- predict(model2,train_data, type='response')
  res_c <- factor(ifelse(res>0.45,'+','-'))
  res_c 
  confusionMatrix(res_c, as.factor(train_data$A16), positive='+', mode='prec_recall')
  
  #mode3
  model3 <- glm(as.factor(A16) ~ as.factor(A1) + as.factor(A4) + as.factor(A5) + as.factor(A6) + as.factor(A7) + as.factor(A9) + as.factor(A10) + as.factor(A12) + as.factor(A13), data = train_data, family = binomial)
  summary(model3)
  res <- predict(model3,train_data, type='response')
  res_c <- factor(ifelse(res>0.45,'+','-'))
  res_c 
  confusionMatrix(res_c, as.factor(train_data$A16), positive='+', mode='prec_recall')
  
  #mode4_no
  model4 <- glm(as.factor(A16) ~ as.factor(.), data = train_data, family = binomial)
  summary(model4)
  res <- predict(model4,train_data, type='response')
  res_c <- factor(ifelse(res>0.45,'+','-'))
  res_c 
  confusionMatrix(res_c, as.factor(train_data$A16), positive='+', mode='prec_recall')
  
  #predict
  prediction <- predict(model2, newdata = test_data, type = 'response')
  prediction_c <- factor(ifelse(prediction > 0.45, '+', '-'))
  prediction_c
  confusionMatrix(prediction_c, as.factor(test_data$A16), positive = '+', mode = 'prec_recall')
  