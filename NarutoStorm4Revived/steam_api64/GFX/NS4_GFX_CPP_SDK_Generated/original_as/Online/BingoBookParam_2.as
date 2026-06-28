package script.net_bingo
{
   public class BingoBookParam
   {
      
      public var m_rare:int = 0;
      
      public var m_iconCode:String = "";
      
      public var m_nameCode:String = "";
      
      public var m_itemMsg:String = "";
      
      public var m_itemNum:int = 0;
      
      public var m_categoryNo:int = 0;
      
      public var m_xfbinname:String = "";
      
      public var m_isDowned:Boolean = false;
      
      public function BingoBookParam(param1:int, param2:String, param3:String, param4:String, param5:int, param6:int, param7:String, param8:Boolean)
      {
         super();
         this.m_rare = param1;
         this.m_iconCode = param2;
         this.m_nameCode = param3;
         this.m_itemMsg = param4;
         this.m_itemNum = param5;
         this.m_categoryNo = param6;
         this.m_xfbinname = param7;
         this.m_isDowned = param8;
      }
   }
}

