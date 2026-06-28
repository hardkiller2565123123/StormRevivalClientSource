package start_top_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class smb_menu_5 extends MovieClip
   {
      
      public var txt_menu:smb_font;
      
      public function smb_menu_5()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_menu.SetTextColor(16771961);
         this.txt_menu.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_menu.SetTextSize(33);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_menu.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_menu.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_menu.SetTextSize(33);
      }
   }
}

