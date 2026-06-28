package script.adv_msion
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   public class nut_msion_win extends MovieClip
   {
      
      public function nut_msion_win()
      {
         var _loc2_:MovieClip = null;
         super();
         var _loc1_:smb_font = this["mc_txt00"];
         if(_loc1_.IsArabic() == true)
         {
            trace("ChangeArabic ItemIcon");
            _loc2_ = this["mc_rew_bg00"];
            _loc2_.ChangeArabicLayout();
            _loc2_ = this["mc_rew_bg01"];
            _loc2_.ChangeArabicLayout();
            _loc2_ = this["mc_rew_bg02"];
            _loc2_.ChangeArabicLayout();
         }
      }
   }
}

