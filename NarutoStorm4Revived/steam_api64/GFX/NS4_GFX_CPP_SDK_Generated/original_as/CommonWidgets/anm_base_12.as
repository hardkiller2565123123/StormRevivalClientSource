package map_sm_fla
{
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import script.xcmn_font.smb_font;
   import script.xct_fd.nut_xct_fd1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol42")]
   public dynamic class anm_base_12 extends MovieClip
   {
      
      public var all_base:nut_xct_fd1;
      
      public var txt_point:smb_font;
      
      public function anm_base_12()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_point.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_point.SetTextSize(28);
         this.txt_point.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_point.SetTextFieldWidth(600);
         this.txt_point.SetTextScroll(true);
         this.txt_point.SetText(String(ExternalInterface.call("MessageConvert","advMainMenu_034")));
      }
   }
}

