#ifndef BOAT_TYPE_H
#define BOAT_TYPE_H


enum eAisShipType {
  NOT_AVAILABLE         = 0,

  // Special purpose ship (01-09)
  SPECIAL_SCIENCE_RESEARCH = 1,
  SPECIAL_TRAINING         = 2,
  SPECIAL_GOVERNMENT       = 3,
  SPECIAL_ICE_BREAKER      = 4,
  SPECIAL_BUOY_TENDER      = 5,
  SPECIAL_CABLE_LAYER      = 6,
  SPECIAL_PIPE_LAYER       = 7,
  SPECIAL_RESERVED_08      = 8,
  SPECIAL_NO_INFO          = 9,

  // Support vessel (10-19)
  SUPPORT_RESERVED_10  = 10,
  SUPPORT_FPSO         = 11,
  SUPPORT_FISH_FACTORY = 12,
  SUPPORT_FISH_FARM    = 13,
  SUPPORT_OFFSHORE     = 14,
  SUPPORT_RESERVED_15  = 15,
  SUPPORT_RESERVED_16  = 16,
  SUPPORT_CONSTRUCTION = 17,
  SUPPORT_CREW_BOAT    = 18,
  SUPPORT_NO_INFO      = 19,

  // Wing-in-ground vessel (20-29)
  WIG_ALL         = 20,
  WIG_HAZMAT_X    = 21,
  WIG_HAZMAT_Y    = 22,
  WIG_HAZMAT_Z    = 23,
  WIG_HAZMAT_OS   = 24,
  WIG_RESERVED_25 = 25,
  WIG_RESERVED_26 = 26,
  WIG_RESERVED_27 = 27,
  WIG_RESERVED_28 = 28,
  WIG_NO_INFO     = 29,

  // Special craft (30-39)
  FISHING       = 30,
  TOWING        = 31,
  TOWING_LARGE  = 32,
  DREDGER       = 33,
  DIVING        = 34,
  WARSHIP       = 35,
  SAILING       = 36,
  PLEASURE_CRAFT = 37,
  TRAWLER       = 38,
  PATROL        = 39,

  // High-speed craft (40-49)
  HSC_ALL         = 40,
  HSC_HAZMAT_X    = 41,
  HSC_HAZMAT_Y    = 42,
  HSC_HAZMAT_Z    = 43,
  HSC_HAZMAT_OS   = 44,
  HSC_PASSENGER   = 45,
  HSC_RORO        = 46,
  HSC_RESERVED_47 = 47,
  HSC_RESERVED_48 = 48,
  HSC_NO_INFO     = 49,

  // Special craft (50-59)
  PILOT             = 50,
  SAR               = 51,
  TUG               = 52,
  PORT_TENDER       = 53,
  ANTI_POLLUTION    = 54,
  LAW_ENFORCEMENT   = 55,
  SPARE_LOCAL_1     = 56,
  SPARE_LOCAL_2     = 57,
  MEDICAL_TRANSPORT = 58,
  NON_COMBATANT     = 59,

  // Passenger ships (60-69)
  PASSENGER_ALL         = 60,
  PASSENGER_HAZMAT_X    = 61,
  PASSENGER_HAZMAT_Y    = 62,
  PASSENGER_HAZMAT_Z    = 63,
  PASSENGER_HAZMAT_OS   = 64,
  PASSENGER_CRUISE      = 65,
  PASSENGER_FERRY       = 66,
  PASSENGER_EXCURSION   = 67,
  PASSENGER_RESERVED_68 = 68,
  PASSENGER_NO_INFO     = 69,

  // Cargo ships (70-79)
  CARGO_ALL          = 70,
  CARGO_HAZMAT_X     = 71,
  CARGO_HAZMAT_Y     = 72,
  CARGO_HAZMAT_Z     = 73,
  CARGO_HAZMAT_OS    = 74,
  CARGO_BULK         = 75,
  CARGO_CONTAINER    = 76,
  CARGO_RORO         = 77,
  CARGO_LANDING_CRAFT = 78,
  CARGO_NO_INFO      = 79,

  // Tankers (80-89)
  TANKER_ALL          = 80,
  TANKER_HAZMAT_X     = 81,
  TANKER_HAZMAT_Y     = 82,
  TANKER_HAZMAT_Z     = 83,
  TANKER_HAZMAT_OS    = 84,
  TANKER_NON_HAZARDOUS = 85,
  TANKER_TUG_BARGE    = 86,
  TANKER_RESERVED_87  = 87,
  TANKER_RESERVED_88  = 88,
  TANKER_NO_INFO      = 89,

  // Other types (90-99)
  OTHER_ALL        = 90,
  OTHER_HAZMAT_X   = 91,
  OTHER_HAZMAT_Y   = 92,
  OTHER_HAZMAT_Z   = 93,
  OTHER_HAZMAT_OS  = 94,
  OTHER_RESERVED_95 = 95,
  OTHER_RESERVED_96 = 96,
  OTHER_RESERVED_97 = 97,
  OTHER_RESERVED_98 = 98,
  OTHER_NO_INFO    = 99,
};


#endif
