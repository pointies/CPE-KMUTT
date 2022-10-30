library(tidyverse)
library(dplyr)
library(ggplot2)
heart <- read.csv("heart.csv")
heart %>%
  
  #probability distribution function
  group_by(Age) %>%
  ggplot(aes(Age)) +
  geom_histogram(binwidth = 2, color = "black", , fill = "lightblue")

  #CDF
  CDF <- ecdf(heart$Age)
  plot(CDF)

  #Sampling
  quantile(heart$Age, runif(10))