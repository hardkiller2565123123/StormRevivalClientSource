package script.infoData
{
   public class InfoDataBase
   {
      
      protected const CCD_INIT_PARAM_NUM:int = 3;
      
      public var m_saveIdx:uint;
      
      public var m_isEnable:Boolean;
      
      public var m_isNew:Boolean;
      
      public function InfoDataBase(param1:Array)
      {
         super();
         this.m_saveIdx = param1[0];
         this.m_isEnable = param1[1];
         this.m_isNew = param1[2];
      }
   }
}

