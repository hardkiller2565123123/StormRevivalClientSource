package result_s_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public dynamic class anm_rslt_4 extends MovieClip
   {
      
      public var txt_rslt:smb_font;
      
      public function anm_rslt_4()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_rslt.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_rslt.SetTextSize(28);
      }
   }
}

