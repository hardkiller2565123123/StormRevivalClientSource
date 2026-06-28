package modesel_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_unset.smb_base;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class anm_event_12 extends MovieClip
   {
      
      public var smb_base:script.xcmn_unset.smb_base;
      
      public var txt_event:smb_font;
      
      public function anm_event_12()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_event.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_event.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_event.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_event.SetTextSize(30);
         this.txt_event.SetTextFieldWidth(1750);
         this.txt_event.SetTextScroll(true);
         this.txt_event.PlayTextScroll();
      }
   }
}

