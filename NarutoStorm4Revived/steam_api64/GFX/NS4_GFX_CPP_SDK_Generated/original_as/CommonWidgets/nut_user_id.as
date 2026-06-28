package script.xcmn_net
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   public class nut_user_id extends MovieClip
   {
      
      public function nut_user_id()
      {
         super();
      }
      
      public function Set(param1:String) : void
      {
         var _loc2_:smb_font = getChildByName("txt_user_id") as smb_font;
         if(_loc2_ != null)
         {
            _loc2_.SetTextPivot(smb_font.CCD_PIVOT_CC);
            _loc2_.SetText(param1);
         }
      }
   }
}

