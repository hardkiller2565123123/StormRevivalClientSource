package duel_cmn_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol291")]
   public dynamic class nut_credit00_4 extends MovieClip
   {
      
      public var mc_credit00:MovieClip;
      
      public var txt_credit00:smb_font;
      
      public function nut_credit00_4()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         this.txt_credit00.SetTextPivot(smb_font.CCD_PIVOT_CC);
      }
      
      internal function frame2() : *
      {
         this.stop();
      }
      
      internal function frame3() : *
      {
         this.stop();
      }
   }
}

