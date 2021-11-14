// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameState.h"

APongGameState::APongGameState()
{
}


int APongGameState::GetNumberOfPlayerGoals()
{
	return NumberOfPlayerGoals;
}		 
int APongGameState::GetNumberOfAiGoals()
{
	return  NumberOfAiGoals;

}

float APongGameState::GetStartTimer()
{
	return GSStartTimer;
}
