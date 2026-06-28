package script.start_event_s_brt
{
   import Enum.Enum;
   
   public class EventParam
   {
      
      public static const CCD_REWARD_NUM:uint = 2;
      
      public static const CCD_SUB_EVENT_STATE_NONE:uint = Enum.Next(0);
      
      public static const CCD_SUB_EVENT_STATE_WAKE:uint = Enum.Next();
      
      public static const CCD_SUB_EVENT_STATE_REWAKE:uint = Enum.Next();
      
      public static const CCD_SUB_EVENT_STATE_ACCEPT:uint = Enum.Next();
      
      public static const CCD_SUB_EVENT_STATE_REWARD:uint = Enum.Next();
      
      public static const CCD_SUB_EVENT_STATE_CLEAR:uint = Enum.Next();
      
      public static const CCD_SUB_EVENT_STATE_VISIBLED_CLEAR:uint = Enum.Next();
      
      public var subEventId:uint = 0;
      
      public var subEventTitle:String = "";
      
      public var outline:String = "";
      
      public var client:String = "";
      
      public var place:String = "";
      
      public var charIcon:String = "";
      
      public var difficult:int = 0;
      
      public var stats:int = 0;
      
      public var isNew:Boolean = false;
      
      public var isNavi:Boolean = false;
      
      public var isUnlock:Boolean = false;
      
      public var isProgressDisable:* = false;
      
      public var rewardNameCtn:Vector.<String> = new Vector.<String>(CCD_REWARD_NUM);
      
      public var rewardNumCtn:Vector.<int> = new Vector.<int>(CCD_REWARD_NUM);
      
      public var rewardIconTypeCtn:Vector.<String> = new Vector.<String>(CCD_REWARD_NUM);
      
      public var rewardIconDataPathCtn:Vector.<String> = new Vector.<String>(CCD_REWARD_NUM);
      
      public function EventParam(param1:uint, param2:String, param3:String, param4:String, param5:String, param6:int, param7:int, param8:int, param9:Boolean, param10:Boolean, param11:Boolean, param12:Boolean, param13:Array, param14:Array, param15:Array, param16:Array)
      {
         super();
         this.subEventId = param1;
         this.subEventTitle = param2;
         this.outline = param3;
         this.client = param4;
         this.place = param5;
         this.difficult = param7;
         this.stats = param8;
         this.isNew = param9;
         this.isNavi = param10;
         this.isUnlock = param11;
         this.isProgressDisable = param12;
         var _loc17_:uint = 0;
         while(_loc17_ < CCD_REWARD_NUM)
         {
            this.rewardNameCtn[_loc17_] = param13[_loc17_];
            this.rewardNumCtn[_loc17_] = param14[_loc17_];
            this.rewardIconTypeCtn[_loc17_] = param15[_loc17_];
            this.rewardIconDataPathCtn[_loc17_] = param16[_loc17_];
            _loc17_++;
         }
         switch(param6)
         {
            case 94:
               this.charIcon = "icon_khm2";
               break;
            case 95:
               this.charIcon = "icon_skr6";
               break;
            case 96:
               this.charIcon = "icon_hmw1";
               break;
            case 97:
               this.charIcon = "icon_skr6";
               break;
            case 98:
               this.charIcon = "icon_sin4";
               break;
            case 99:
               this.charIcon = "icon_ten4";
               break;
            case 100:
               this.charIcon = "icon_roc4";
               break;
            case 101:
               this.charIcon = "icon_roc4";
               break;
            case 102:
               this.charIcon = "icon_sik5";
               break;
            case 103:
               this.charIcon = "icon_gar6";
               break;
            default:
               this.charIcon = "icon_khm2";
         }
      }
   }
}

