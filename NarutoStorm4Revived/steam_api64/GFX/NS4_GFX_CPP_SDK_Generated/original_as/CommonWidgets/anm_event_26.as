package start_evnt_s_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol56")]
   public dynamic class anm_event_26 extends MovieClip
   {
      
      public var txt_event:smb_font;
      
      public function anm_event_26()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_event.SetTextSize(33);
         this.txt_event.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_event.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

