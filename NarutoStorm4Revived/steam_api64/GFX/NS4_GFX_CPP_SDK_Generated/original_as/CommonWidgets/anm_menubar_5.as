package net_offline_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public dynamic class anm_menubar_5 extends MovieClip
   {
      
      public var txt_menu:smb_font;
      
      public function anm_menubar_5()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_menu.SetTextColor(16774492);
         this.txt_menu.SetDropShadowFilter(6161478);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_menu.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_menu.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

