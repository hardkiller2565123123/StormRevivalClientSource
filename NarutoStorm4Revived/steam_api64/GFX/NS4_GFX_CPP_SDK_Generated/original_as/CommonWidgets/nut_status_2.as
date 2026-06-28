package script.gauge_icon
{
   import flash.display.MovieClip;
   
   public class nut_status extends MovieClip
   {
      
      internal static const ICON_NONE:Number = 0;
      
      internal static const ATK_DOWN:Number = 1;
      
      internal static const ATK_UP:Number = 2;
      
      internal static const DEF_DOWN:Number = 3;
      
      internal static const DEF_UP:Number = 4;
      
      internal static const FAINT:Number = 5;
      
      internal static const GUARDBREAK:Number = 6;
      
      internal static const AWAKE_DOWN:Number = 7;
      
      internal static const AWAKE:Number = 8;
      
      internal static const AUTO_DODGE:Number = 9;
      
      internal static const SACRIFICE:Number = 10;
      
      internal static const SACRIFICE_EX:Number = 11;
      
      internal static const POISON:Number = 12;
      
      internal static const SLEEP:Number = 13;
      
      internal static const SUPERARMOUR:Number = 14;
      
      internal static const SUPERARMOUR_EX:Number = 15;
      
      internal static const SPEEDDOWN:Number = 16;
      
      internal static const SPEEDUP:Number = 17;
      
      internal static const PROJ_THROUGH:Number = 18;
      
      internal static const PROJ_THROUGH_EX:Number = 19;
      
      internal static const UNITY:Number = 20;
      
      internal static const UNITY_EX:Number = 21;
      
      internal static const ADD_POISON:Number = 22;
      
      internal static const CHAKRA_UP:Number = 23;
      
      internal static const CHA_CONSUM_DOWN:Number = 24;
      
      internal static const SPT_REC_SPD_UP:Number = 27;
      
      internal static const LIFE_AUTO_REC:Number = 35;
      
      internal static const GUARDBREAK_UP:Number = 36;
      
      internal static const CHAKRA_AUTO_REC:Number = 37;
      
      internal static const STORM_GAGUE_UP:Number = 38;
      
      public function nut_status()
      {
         super();
      }
      
      public function ChangeIcon(param1:int) : void
      {
         var _loc2_:* = "";
         switch(param1)
         {
            case ATK_DOWN:
               _loc2_ = "st_00";
               break;
            case ATK_UP:
               _loc2_ = "st_01";
               break;
            case DEF_DOWN:
               _loc2_ = "st_02";
               break;
            case DEF_UP:
               _loc2_ = "st_03";
               break;
            case FAINT:
               _loc2_ = "st_04";
               break;
            case GUARDBREAK:
               _loc2_ = "st_05";
               break;
            case AWAKE_DOWN:
               _loc2_ = "st_06";
               break;
            case AWAKE:
               _loc2_ = "st_07";
               break;
            case AUTO_DODGE:
               _loc2_ = "st_08";
               break;
            case SACRIFICE:
               _loc2_ = "st_09";
               break;
            case SACRIFICE_EX:
               _loc2_ = "st_10";
               break;
            case POISON:
               _loc2_ = "st_11";
               break;
            case SLEEP:
               _loc2_ = "st_12";
               break;
            case SUPERARMOUR:
               _loc2_ = "st_13";
               break;
            case SUPERARMOUR_EX:
               _loc2_ = "st_14";
               break;
            case SPEEDDOWN:
               _loc2_ = "st_15";
               break;
            case SPEEDUP:
               _loc2_ = "st_16";
               break;
            case PROJ_THROUGH:
               _loc2_ = "st_17";
               break;
            case PROJ_THROUGH_EX:
               _loc2_ = "st_18";
               break;
            case UNITY:
               _loc2_ = "st_19";
               break;
            case UNITY_EX:
               _loc2_ = "st_20";
               break;
            case ADD_POISON:
               _loc2_ = "st_21";
               break;
            case CHAKRA_UP:
               _loc2_ = "st_22";
               break;
            case CHA_CONSUM_DOWN:
               _loc2_ = "st_23";
               break;
            case SPT_REC_SPD_UP:
               _loc2_ = "st_27";
               break;
            case LIFE_AUTO_REC:
               _loc2_ = "st_24";
               break;
            case GUARDBREAK_UP:
               _loc2_ = "st_25";
               break;
            case CHAKRA_AUTO_REC:
               _loc2_ = "st_26";
               break;
            case STORM_GAGUE_UP:
               _loc2_ = "st_28";
         }
         this.gotoAndStop(_loc2_);
      }
   }
}

