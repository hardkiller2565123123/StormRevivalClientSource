package option_keyboard_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base2;
   import script.xcmn_menu.nut_base3;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol17")]
   public dynamic class anm_set_5 extends MovieClip
   {
      
      public var all_base3:nut_base3;
      
      public var all_base2:nut_base2;
      
      public var txt_set:smb_font;
      
      public function anm_set_5()
      {
         super();
         addFrameScript(0,this.frame1,6,this.frame7,7,this.frame8);
      }
      
      internal function frame1() : *
      {
         this.txt_set.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_set.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame7() : *
      {
         stop();
         this.txt_set.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_set.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame8() : *
      {
         stop();
         this.txt_set.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_set.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

