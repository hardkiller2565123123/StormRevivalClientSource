package Struct
{
   public class ThaiInfo
   {
      
      public var m_charCode:Number;
      
      public var m_stringIndex:int;
      
      public var m_lineNum:int;
      
      public var m_textFieldIndex:int;
      
      public var m_isUsedSecondLineConsonant:Boolean;
      
      public function ThaiInfo(param1:Number, param2:int, param3:int, param4:int, param5:Boolean)
      {
         super();
         this.m_charCode = param1;
         this.m_stringIndex = param2;
         this.m_lineNum = param3;
         this.m_textFieldIndex = param4;
         this.m_isUsedSecondLineConsonant = param5;
      }
   }
}

