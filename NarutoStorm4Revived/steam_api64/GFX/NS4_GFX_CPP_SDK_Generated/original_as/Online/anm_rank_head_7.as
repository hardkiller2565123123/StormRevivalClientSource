package net_rank_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public dynamic class anm_rank_head_7 extends MovieClip
   {
      
      public var mc_txt_bp:MovieClip;
      
      public var mc_txt_title:MovieClip;
      
      public var mc_wins_per:MovieClip;
      
      public var txt_id:smb_font;
      
      public var txt_ranking:smb_font;
      
      public function anm_rank_head_7()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         this.txt_ranking.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ranking.SetTextColor(12305407);
         this.txt_ranking.SetTextFieldWidth(260);
         this.txt_ranking.SetTextFit(true);
         this.txt_id.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_id.SetTextColor(12305407);
         this.txt_id.SetTextFieldWidth(420);
         this.txt_id.SetTextFit(true);
      }
      
      internal function frame2() : *
      {
      }
      
      internal function frame3() : *
      {
         stop();
      }
   }
}

