package script.duel_boss_help
{
   import Struct.MessageParam;
   
   public class nut_help_phase02
   {
      
      public static const CCD_KEY_ATK:int = 0;
      
      public static const CCD_KEY_SRK:int = 1;
      
      public static const CCD_HELP_NUM:int = 2;
      
      private const CCD_HELP_MSG_1:String = "左に移動";
      
      private const CCD_HELP_MSG_2:String = "右に移動";
      
      private const CCD_LMO_CMD:String = "<icon stk_r_l>";
      
      private const CCD_RMO_CMD:String = "<icon stk_r_r>";
      
      private var m_paramArr:Array = new Array();
      
      public function nut_help_phase02()
      {
         super();
         this.m_paramArr.push(new MessageParam(this.CCD_HELP_MSG_1,this.CCD_LMO_CMD));
         this.m_paramArr.push(new MessageParam(this.CCD_HELP_MSG_2,this.CCD_RMO_CMD));
      }
      
      public function GetMessage(param1:int) : String
      {
         var _loc2_:String = "UndefinedMessage";
         if(this.m_paramArr[param1] != null)
         {
            _loc2_ = this.m_paramArr[param1].m_msg;
         }
         return _loc2_;
      }
      
      public function GetCommand(param1:int) : String
      {
         var _loc2_:String = "UndefinedMessage";
         if(this.m_paramArr[param1] != null)
         {
            _loc2_ = this.m_paramArr[param1].m_cmd;
         }
         return _loc2_;
      }
   }
}

