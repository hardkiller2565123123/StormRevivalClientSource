package script.infoData
{
   public class SlotData
   {
      
      public var m_leaderId:String = null;
      
      public var m_support1Id:String = null;
      
      public var m_support2Id:String = null;
      
      public var m_leaderType:int = 0;
      
      public var m_support1Type:int = 0;
      
      public var m_support2Type:int = 0;
      
      public function SlotData(param1:String = null, param2:String = null, param3:String = null, param4:int = 0, param5:int = 0, param6:int = 0)
      {
         super();
         this.m_leaderId = param1;
         this.m_support1Id = param2;
         this.m_support2Id = param3;
         this.m_leaderType = param4;
         this.m_support1Type = param5;
         this.m_support2Type = param6;
      }
      
      public function Reset() : *
      {
         this.m_leaderId = null;
         this.m_support1Id = null;
         this.m_support2Id = null;
         this.m_leaderType = 0;
         this.m_support1Type = 0;
         this.m_support2Type = 0;
      }
   }
}

