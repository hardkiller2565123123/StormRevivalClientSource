package script.map_sm
{
   public class JumpIconInfo
   {
      
      public var m_stageId:String = "";
      
      public var m_msgId:String = "";
      
      public var m_iconX:Number = 0;
      
      public var m_iconY:Number = 0;
      
      public function JumpIconInfo(param1:String, param2:String, param3:Number, param4:Number)
      {
         super();
         this.m_stageId = param1;
         this.m_msgId = param2;
         this.m_iconX = param3;
         this.m_iconY = param4;
      }
   }
}

