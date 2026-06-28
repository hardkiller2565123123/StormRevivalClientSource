package start_evnt_s_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol57")]
   public dynamic class anm_allclear_28 extends MovieClip
   {
      
      public var txt_clear:smb_font;
      
      public function anm_allclear_28()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_clear.SetText("ALL CLEAR");
         this.txt_clear.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_clear.SetTextColor(16776635);
         this.txt_clear.SetTextSize(44);
      }
   }
}

