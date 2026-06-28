package script.adv_msion
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol16")]
   public class anm_txt00 extends MovieClip
   {
      
      internal static const CCD_ARABIC_REWARD_TEXT_POS_X:Number = 225;
      
      internal static const CCD_ARABIC_REWARD_NUM_TEXT_POS_X:Number = -405;
      
      public var txt_client:smb_font;
      
      public var txt_difi:smb_font;
      
      public var txt_head00:smb_font;
      
      public var txt_head02:smb_font;
      
      public var txt_rew_x1:smb_font;
      
      public var txt_rew_x2:smb_font;
      
      public var txt_rew_x3:smb_font;
      
      public var txt_reward00:smb_font;
      
      public var txt_reward01:smb_font;
      
      public var txt_reward02:smb_font;
      
      private var m_rewardCtn:Array = new Array();
      
      private var m_rewardNumCtn:Array = new Array();
      
      public function anm_txt00()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_rewardCtn.push(this["txt_reward00"]);
         this.m_rewardCtn.push(this["txt_reward01"]);
         this.m_rewardCtn.push(this["txt_reward02"]);
         this.m_rewardNumCtn.push(this["txt_rew_x1"]);
         this.m_rewardNumCtn.push(this["txt_rew_x2"]);
         this.m_rewardNumCtn.push(this["txt_rew_x3"]);
      }
      
      public function IsArabic() : Boolean
      {
         var _loc1_:Boolean = false;
         if(this.m_rewardCtn[0] != null)
         {
            _loc1_ = Boolean(this.m_rewardCtn[0].IsArabic());
         }
         return _loc1_;
      }
      
      private function CheckArabic() : *
      {
         var _loc1_:Point = null;
         var _loc2_:int = 0;
         if(this.IsArabic() == true)
         {
            _loc1_ = new Point();
            _loc2_ = 0;
            while(_loc2_ < this.m_rewardCtn.length)
            {
               this.m_rewardCtn[_loc2_].GetTextPos(_loc1_);
               this.m_rewardCtn[_loc2_].SetTextPos(CCD_ARABIC_REWARD_TEXT_POS_X,_loc1_.y);
               this.m_rewardCtn[_loc2_].SetTextPivot(smb_font.CCD_PIVOT_RC);
               this.m_rewardCtn[_loc2_].SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
               this.m_rewardNumCtn[_loc2_].GetTextPos(_loc1_);
               this.m_rewardNumCtn[_loc2_].SetTextPos(CCD_ARABIC_REWARD_NUM_TEXT_POS_X,_loc1_.y);
               this.m_rewardNumCtn[_loc2_].SetTextPivot(smb_font.CCD_PIVOT_LC);
               this.m_rewardNumCtn[_loc2_].SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
               _loc2_++;
            }
         }
      }
      
      internal function frame1() : *
      {
         this.txt_difi.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_difi.SetTextSize(23);
         this.txt_head00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head00.SetTextColor(16777215);
         this.txt_head00.SetTextSize(28);
         this.txt_head02.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head02.SetTextColor(16777215);
         this.txt_head02.SetTextSize(28);
         this.txt_client.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_client.SetTextColor(0);
         this.txt_client.SetTextSize(30);
         this.txt_client.SetTextFieldWidth(420);
         this.txt_client.SetTextFit(true);
         this.txt_reward00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_reward00.SetTextColor(0);
         this.txt_reward00.SetTextSize(30);
         this.txt_reward00.SetTextFieldWidth(555);
         this.txt_reward00.SetTextFit(true);
         this.txt_reward01.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_reward01.SetTextColor(0);
         this.txt_reward01.SetTextSize(30);
         this.txt_reward01.SetTextFieldWidth(555);
         this.txt_reward01.SetTextFit(true);
         this.txt_reward02.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_reward02.SetTextColor(0);
         this.txt_reward02.SetTextSize(30);
         this.txt_reward02.SetTextFieldWidth(555);
         this.txt_reward02.SetTextFit(true);
         this.txt_rew_x1.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_rew_x1.SetTextColor(0);
         this.txt_rew_x1.SetTextSize(30);
         this.txt_rew_x2.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_rew_x2.SetTextColor(0);
         this.txt_rew_x2.SetTextSize(30);
         this.txt_rew_x3.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_rew_x3.SetTextColor(0);
         this.txt_rew_x3.SetTextSize(30);
         this.CheckArabic();
      }
   }
}

