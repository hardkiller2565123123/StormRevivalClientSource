package freebtl_set_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base2;
   import script.xcmn_menu.nut_base3;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol42")]
   public dynamic class nut_set_4 extends MovieClip
   {
      
      public var mc_set_base1:nut_base3;
      
      public var mc_set_base2:nut_base2;
      
      public var txt_end:smb_font;
      
      public function nut_set_4()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_end.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_end.SetTextSize(33);
         this.txt_end.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_end.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_end.SetTextFieldWidth(720);
         this.txt_end.SetTextFit(true);
      }
   }
}

