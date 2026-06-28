package start_evnt_s_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol43")]
   public dynamic class anm_event_2 extends MovieClip
   {
      
      public var txt_event:smb_font;
      
      public function anm_event_2()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_event.SetTextSize(50);
         this.txt_event.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_event.SetTextColor(12136817);
         this.txt_event.SetTextFieldWidth(1150);
         this.txt_event.SetTextFit(true);
      }
   }
}

