package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcp_frame1.smb_xcp_frame1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol32")]
   public dynamic class smb_btl_set_15 extends MovieClip
   {
      
      public var mc_base2:smb_xcp_frame1;
      
      public var txt_btl_cond:smb_font;
      
      public function smb_btl_set_15()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_btl_cond.SetText("1.バトルに勝利するABC_gy");
         this.txt_btl_cond.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_btl_cond.SetTextSize(28);
         this.txt_btl_cond.SetTextFieldWidth(930);
         this.txt_btl_cond.SetTextFit(true);
      }
   }
}

