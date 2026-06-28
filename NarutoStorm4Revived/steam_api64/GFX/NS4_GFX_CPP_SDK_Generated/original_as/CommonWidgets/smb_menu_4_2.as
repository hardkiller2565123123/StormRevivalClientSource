package start_top_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class smb_menu_4 extends MovieClip
   {
      
      public var txt_menu:smb_font;
      
      public function smb_menu_4()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_menu.SetTextColor(16771961);
         this.txt_menu.DisableDropShadowFilter();
         this.txt_menu.SetTextSize(34);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_menu.SetTextColor(13882323);
         this.txt_menu.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_menu.SetTextSize(34);
      }
   }
}

