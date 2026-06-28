package script.xcmn_menu
{
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import script.xcmn_font.smb_font;
   
   public class nut_money extends MovieClip
   {
      
      internal static const MONEY_MAX:Number = 9999999;
      
      public function nut_money()
      {
         super();
      }
      
      public function SetMoney(param1:int) : *
      {
         var _loc3_:String = null;
         var _loc4_:Array = null;
         if(param1 > MONEY_MAX)
         {
            param1 = MONEY_MAX;
         }
         var _loc2_:smb_font = getChildByName("txt_money") as smb_font;
         if(_loc2_ != null)
         {
            _loc3_ = "" + param1 as String;
            _loc4_ = [_loc3_];
            _loc2_.SetText(String(ExternalInterface.call("MessageConvert","MSG_Money")));
            _loc2_.ReplaceTextList(_loc4_);
         }
      }
   }
}

