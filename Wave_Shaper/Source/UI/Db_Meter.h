/*
  ==============================================================================

    Db_Metering.h
    Created: 20 May 2022 5:39:30pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once
#include "Juceheader.h"

class DBMeter : public Component

{
public:
 
    /*%%*/
    DBMeter();
    
    /*%%*/
    ~DBMeter();
    
    /*%%*/
    void paint(Graphics& g) override;
    
    /*%%*/
    void resized() override;
    
    
private:
};
