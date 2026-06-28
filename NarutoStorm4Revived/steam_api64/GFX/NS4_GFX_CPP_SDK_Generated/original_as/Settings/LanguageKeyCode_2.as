package Language
{
   import flash.external.ExternalInterface;
   
   public class LanguageKeyCode
   {
      
      private var CCD_LANG_JAPANESE:* = 0;
      
      private var CCD_LANG_PORTUGUESE_BR:* = 0;
      
      private var CCD_LANG_RUSSIAN:* = 0;
      
      private var CCD_LANG_CHINESE_T:* = 0;
      
      private var CCD_LANG_CHINESE_S:* = 0;
      
      private var CCD_LANG_ENGLISH:* = 0;
      
      private var CCD_LANG_ARABIC:* = 0;
      
      private var CCD_LANG_KOREAN:* = 0;
      
      public function LanguageKeyCode()
      {
         super();
         this.CCD_LANG_JAPANESE = int(ExternalInterface.call("GetLangJapanese"));
         this.CCD_LANG_PORTUGUESE_BR = int(ExternalInterface.call("GetLangPortuguese_Br"));
         this.CCD_LANG_RUSSIAN = int(ExternalInterface.call("GetLangRussian"));
         this.CCD_LANG_CHINESE_T = int(ExternalInterface.call("GetLangChinese_T"));
         this.CCD_LANG_CHINESE_S = int(ExternalInterface.call("GetLangChinese_S"));
         this.CCD_LANG_ENGLISH = int(ExternalInterface.call("GetLangEnglish"));
         this.CCD_LANG_ARABIC = int(ExternalInterface.call("GetLangArabic"));
         this.CCD_LANG_KOREAN = int(ExternalInterface.call("GetLangKorean"));
      }
      
      public function GetJapaneseKeyCode() : int
      {
         return this.CCD_LANG_JAPANESE;
      }
      
      public function GetLangPortuguese_BrKeyCode() : int
      {
         return this.CCD_LANG_PORTUGUESE_BR;
      }
      
      public function GetLangRussianKeyCode() : int
      {
         return this.CCD_LANG_RUSSIAN;
      }
      
      public function GetLangChinese_tKeyCode() : int
      {
         return this.CCD_LANG_CHINESE_T;
      }
      
      public function GetLangChinese_sKeyCode() : int
      {
         return this.CCD_LANG_CHINESE_S;
      }
      
      public function GetLangEnglishKeyCode() : int
      {
         return this.CCD_LANG_ENGLISH;
      }
      
      public function GetArabicKeyCode() : int
      {
         return this.CCD_LANG_ARABIC;
      }
      
      public function GetLangKoreanKeyCode() : int
      {
         return this.CCD_LANG_KOREAN;
      }
      
      public function GetGameSetLang() : int
      {
         return int(ExternalInterface.call("GetGameSetLang"));
      }
   }
}

