package Struct
{
   public class MessageParam
   {
      
      public var m_msg:String = "";
      
      public var m_cmd:String = "";
      
      public function MessageParam(param1:String = "", param2:String = "")
      {
         super();
         this.m_msg = param1;
         this.m_cmd = param2;
      }
   }
}

