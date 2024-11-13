static const char *const qpiriList[][30] = {
    // [PI34 / MPPT-3000], [PI30 HS MS MSX], [PI30 Revo], [PI30 PIP], [PI41 / LV5048]
    {
DESCR_AC_In_Rating_Voltage,            // BBB.B
DESCR_AC_In_Rating_Current,            // CC.C
DESCR_AC_Out_Rating_Voltage,           // DDD.D
DESCR_AC_Out_Rating_Frequency,         // EE.E
DESCR_AC_Out_Rating_Current,           // FF.F
DESCR_AC_Out_Rating_Apparent_Power,    // HHHH
DESCR_AC_Out_Rating_Active_Power,      // IIII
DESCR_Battery_Rating_Voltage,          // JJ.J
DESCR_Battery_Recharge_Voltage,       // KK.K
DESCR_Battery_Under_Voltage,           // JJ.J
DESCR_Battery_Bulk_Voltage,            // KK.K
DESCR_Battery_Float_Voltage,           // LL.L
DESCR_Battery_Type,                    // O
DESCR_Current_Max_AC_Charging_Current, // PP
DESCR_Current_Max_Charging_Current,    // QQ0
DESCR_Input_Voltage_Range,             // O
DESCR_Output_Source_Priority,          // P
DESCR_Charger_Source_Priority,         // Q
DESCR_Parallel_Max_Num,                // R
DESCR_Machine_Type,                    // SS
DESCR_Topology,                        // T
DESCR_Output_Mode,                     // U
DESCR_Battery_Redischarge_Voltage,    // VV.V
DESCR_PV_OK_Condition_For_Parallel,    // W
DESCR_PV_Power_Balance,                // X
DESCR_Max_Charging_Time_At_CV_Stage,   // YYY
DESCR_Operation_Logic,                 // Z
DESCR_Max_Discharging_Current,         // CCC
    },
    // [PI16]
    {
DESCR_AC_In_Rating_Voltage,            // BBB.B
DESCR_AC_In_Rating_Current,            // CC.C
DESCR_AC_Out_Rating_Voltage,           // DDD.D
DESCR_AC_Out_Rating_Frequency,         // EE.E
DESCR_AC_Out_Rating_Current,           // FF.F
DESCR_AC_Out_Rating_Apparent_Power,    // HHHH
DESCR_AC_Out_Rating_Active_Power,      // IIII
DESCR_Battery_Rating_Voltage,          // JJ.J
DESCR_Battery_Recharge_Voltage,       // KK.K
DESCR_Battery_Under_Voltage,           // JJ.J
DESCR_Battery_Bulk_Voltage,            // KK.K
DESCR_Battery_Float_Voltage,           // LL.L
DESCR_Battery_Type,                    // O
DESCR_Current_Max_AC_Charging_Current, // PP
DESCR_Current_Max_Charging_Current,    // QQ0
DESCR_Input_Voltage_Range,             // O
DESCR_Output_Source_Priority,          // P
DESCR_Charger_Source_Priority,         // Q
DESCR_Parallel_Max_Num,                // R
DESCR_Machine_Type,                    // SS
DESCR_Topology,                        // T
DESCR_Output_Mode,                     // U
DESCR_Battery_Redischarge_Voltage,    // VV.V
DESCR_PV_OK_Condition_For_Parallel,    // W
DESCR_PV_Power_Balance,                // X
DESCR_Max_Charging_Time_At_CV_Stage,   // YYY
DESCR_Operation_Logic,                 // Z
DESCR_Max_Discharging_Current,         // CCC
    },
};
static const char *const P007PIRI[][25] = {
    // [PI34 / MPPT-3000], [PI30 HS MS MSX], [PI30 Revo], [PI30 PIP], [PI41 / LV5048]

    {DESCR_AC_In_Rating_Voltage, "10"},           // AAAA
    {DESCR_AC_In_Rating_Current, "10"},           // BBB
    {DESCR_AC_Out_Rating_Voltage, "10"},          // CCCC
    {DESCR_AC_Out_Rating_Frequency, "10"},        // DDD
    {DESCR_AC_Out_Rating_Current, "10"},          // EEE
    {DESCR_AC_Out_Rating_Apparent_Power, "0"},    // FFFF
    {DESCR_AC_Out_Rating_Active_Power, "0"},      // IIII
    {DESCR_Battery_Rating_Voltage, "10"},         // HHH
    {DESCR_Battery_Recharge_Voltage, "10"},      // III
    {DESCR_Battery_Redischarge_Voltage, "10"},   // JJJ
    {DESCR_Battery_Under_Voltage, "10"},          // KKK
    {DESCR_Battery_Bulk_Voltage, "10"},           // LLL
    {DESCR_Battery_Float_Voltage, "10"},          // MMM
    {DESCR_Battery_Type, "0"},                    // N
    {DESCR_Current_Max_AC_Charging_Current, "0"}, // OO
    {DESCR_Current_Max_Charging_Current, "0"},    // PPP
    {DESCR_Input_Voltage_Range, "0"},             // Q
    {DESCR_Output_Source_Priority, "0"},          // R
    {DESCR_Charger_Source_Priority, "0"},         // S
    {DESCR_Parallel_Max_Num, "0"},                // T
    {DESCR_Machine_Type, "0"},                    // U
    {DESCR_Topology, "0"},                        // V
    {DESCR_Output_Mode, "0"},                     // W
    {DESCR_Solar_Power_Priority, "0"},            // Z
    {DESCR_MPPT_String, "0"},                     // a
};
bool PI_Serial::PIXX_QPIRI()
{
  if (protocol == PI30)
  {
    String commandAnswer = this->requestData("QPIRI");
    get.raw.qpiri = commandAnswer;
    // calculate the length with https://elmar-eigner.de/text-zeichen-laenge.html
    if (commandAnswer == DESCR_req_NAK || commandAnswer == DESCR_req_NOA)
    {
      return true;
    }
    if (commandAnswer == DESCR_req_ERCRC)
    {
      return false;
    }
    if (commandAnswer.length() > 80 &&
        commandAnswer.length() <= 108)
    {

      byte protocolNum = 0;
      String strs[30];
      // Split the string into substrings
      int StringCount = 0;
      while (commandAnswer.length() > 0)
      {
        int index = commandAnswer.indexOf(delimiter);
        if (index == -1) // No space found
        {
          strs[StringCount++] = commandAnswer;
          break;
        }
        else
        {
          strs[StringCount++] = commandAnswer.substring(0, index);
          commandAnswer = commandAnswer.substring(index + 1);
        }
      }

      for (unsigned int i = 0; i < sizeof qpiriList[protocolNum] / sizeof qpiriList[protocolNum][0]; i++)
      {
        if (!strs[i].isEmpty() && strcmp(qpiriList[protocolNum][i], "") != 0)
          staticData[qpiriList[protocolNum][i]] = (int)(strs[i].toFloat() * 100 + 0.5) / 100.0;
      }

      switch ((byte)staticData[DESCR_Battery_Type].as<unsigned int>())
      {
      case 0:
        staticData[DESCR_Battery_Type] = "AGM";
        break;
      case 1:
        staticData[DESCR_Battery_Type] = "Flooded";
        break;
      case 2:
        staticData[DESCR_Battery_Type] = "User";
        break;
      default:
        break;
      }
      switch ((byte)staticData[DESCR_Input_Voltage_Range].as<unsigned int>())
      {
      case 0:
        staticData[DESCR_Input_Voltage_Range] = "Appliance";
        break;
      case 1:
        staticData[DESCR_Input_Voltage_Range] = "UPS";
        break;
      default:
        break;
      }
      switch ((byte)staticData[DESCR_Output_Source_Priority].as<unsigned int>())
      {
      case 0:
        staticData[DESCR_Output_Source_Priority] = "Utility first";
        break;
      case 1:
        staticData[DESCR_Output_Source_Priority] = "Solar first";
        break;
      case 2:
        staticData[DESCR_Output_Source_Priority] = "SBU first";
        break;
      default:
        break;
      }
      switch ((byte)staticData[DESCR_Charger_Source_Priority].as<unsigned int>())
      {
      case 0:
        staticData[DESCR_Charger_Source_Priority] = "Utility first";
        break;
      case 1:
        staticData[DESCR_Charger_Source_Priority] = "Solar first";
        break;
      case 2:
        staticData[DESCR_Charger_Source_Priority] = "Solar + Utility";
        break;
      case 3:
        staticData[DESCR_Charger_Source_Priority] = "Only solar charging permitted";
        break;
      default:
        break;
      }
      switch ((byte)staticData[DESCR_Machine_Type].as<unsigned int>())
      {
      case 00:
        staticData[DESCR_Machine_Type] = "Grid tie";
        break;
      case 01:
        staticData[DESCR_Machine_Type] = "Off Grid";
        break;
      case 10:
        staticData[DESCR_Machine_Type] = "Hybrid";
        break;
      default:
        break;
      }
      switch ((byte)staticData[DESCR_Topology])
      {
      case 0:
        staticData[DESCR_Topology] = "Transformerless";
        break;
      case 1:
        staticData[DESCR_Topology] = "Transformer";
        break;
      default:
        break;
        return true;
      }
      return true;
    }
    return true;
  }
  else if (protocol == PI18)
  {
    String commandAnswer = this->requestData("^P007PIRI");
    get.raw.qpiri = commandAnswer;
    if (commandAnswer == DESCR_req_NAK || commandAnswer == DESCR_req_NOA)
    {
      return true;
    }
    if (commandAnswer == DESCR_req_ERCRC)
    {
      return false;
    }
    if (commandAnswer.length() > 80 &&
        commandAnswer.length() < 105)
    {
      String strs[30];
      // Split the string into substrings
      int StringCount = 0;
      while (commandAnswer.length() > 0)
      {
        int index = commandAnswer.indexOf(delimiter);
        if (index == -1) // No space found
        {
          strs[StringCount++] = commandAnswer;
          break;
        }
        else
        {
          strs[StringCount++] = commandAnswer.substring(0, index);
          commandAnswer = commandAnswer.substring(index + 1);
        }
      }

      for (unsigned int i = 0; i < sizeof P007PIRI[0] / sizeof P007PIRI[0][0]; i++)
      {
        if (!strs[i].isEmpty() && strcmp(P007PIRI[i][0], "") != 0)
        {
          if (atoi(P007PIRI[i][1]) > 0)
          {
            staticData[P007PIRI[i][0]] = (int)((strs[i].toFloat() / atoi(P007PIRI[i][1])) * 100 + 0.5) / 100.0;
          }
          else if (atoi(P007PIRI[i][1]) == 0)
          {
            staticData[P007PIRI[i][0]] = strs[i].toInt();
          }
          else
          {
            staticData[P007PIRI[i][0]] = strs[i];
          }
          // staticData[qpiriList[0][i]] = (int)(strs[i].toFloat() * 100 + 0.5) / 100.0;
        }
      }

      switch ((byte)staticData[DESCR_Battery_Type].as<unsigned int>())
      {
      case 0:
        staticData[DESCR_Battery_Type] = "AGM";
        break;
      case 1:
        staticData[DESCR_Battery_Type] = "Flooded";
        break;
      case 2:
        staticData[DESCR_Battery_Type] = "User";
        break;
      default:
        break;
      }
      switch ((byte)staticData[DESCR_Input_Voltage_Range].as<unsigned int>())
      {
      case 0:
        staticData[DESCR_Input_Voltage_Range] = "Appliance";
        break;
      case 1:
        staticData[DESCR_Input_Voltage_Range] = "UPS";
        break;
      default:
        break;
      }
      switch ((byte)staticData[DESCR_Output_Source_Priority].as<unsigned int>())
      {
      case 0:
        staticData[DESCR_Output_Source_Priority] = "Solar-Utility-Battery";
        break;
      case 1:
        staticData[DESCR_Output_Source_Priority] = "Solar-Battery-Utility";
        break;
      default:
        break;
      }
      switch ((byte)staticData[DESCR_Charger_Source_Priority].as<unsigned int>())
      {
      case 0:
        staticData[DESCR_Charger_Source_Priority] = "Solar first";
        break;
      case 1:
        staticData[DESCR_Charger_Source_Priority] = "Solar and Utility";
        break;
      case 2:
        staticData[DESCR_Charger_Source_Priority] = "Only solar";
        break;
      default:
        break;
      }
      switch ((byte)staticData[DESCR_Machine_Type].as<unsigned int>())
      {
      case 0:
        staticData[DESCR_Machine_Type] = "Off-grid Tie";
        break;
      case 1:
        staticData[DESCR_Machine_Type] = "Grid-Tie";
        break;
      default:
        break;
      }
      switch ((byte)staticData[DESCR_Topology])
      {
      case 0:
        staticData[DESCR_Topology] = "Transformerless";
        break;
      case 1:
        staticData[DESCR_Topology] = "Transformer";
        break;
      default:
        break;
        return true;
      }
      switch ((byte)staticData[DESCR_Output_Mode].as<unsigned int>())
      {
      case 0:
        staticData[DESCR_Output_Mode] = "Single module";
        break;
      case 1:
        staticData[DESCR_Output_Mode] = "parallel output";
        break;
      case 2:
        staticData[DESCR_Output_Mode] = "Phase 1 of three phase output";
        break;
      case 3:
        staticData[DESCR_Output_Mode] = "Phase 2 of three phase output";
        break;
      case 4:
        staticData[DESCR_Output_Mode] = "Phase 3 of three phase";
        break;
      default:
        break;
        return true;
      }
      switch ((byte)staticData[DESCR_Solar_Power_Priority].as<unsigned int>())
      {
      case 0:
        staticData[DESCR_Solar_Power_Priority] = "Battery-Load-Utility";
        break;
      case 1:
        staticData[DESCR_Solar_Power_Priority] = "Load-Battery-Utility";
        break;
      default:
        break;
        return true;
      }

      return true;
    }
    return true;
  }
  else if (protocol == NoD)
  {
    return false;
  }
  else
  {
    return false;
  }
}