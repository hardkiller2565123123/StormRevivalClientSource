package stagesel_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol20")]
   public dynamic class anm_caution_6 extends MovieClip
   {
      
      public var mc_caution_b:MovieClip;
      
      public var txt_caution:smb_font;
      
      public function anm_caution_6()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_caution.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_caution.SetTextColor(16507777);
         this.txt_caution.SetTextSize(35);
      }
   }
}

