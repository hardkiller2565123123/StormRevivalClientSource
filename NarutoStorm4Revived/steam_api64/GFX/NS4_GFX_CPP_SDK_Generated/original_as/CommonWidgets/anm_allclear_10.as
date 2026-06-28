package start_evnt_s_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol44")]
   public dynamic class anm_allclear_10 extends MovieClip
   {
      
      public var txt_clear:smb_font;
      
      public function anm_allclear_10()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_clear.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_clear.SetTextSize(49);
      }
   }
}

