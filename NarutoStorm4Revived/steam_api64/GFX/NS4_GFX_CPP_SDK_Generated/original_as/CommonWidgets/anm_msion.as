package script.start_event_s_brt
{
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import script.adv_msion.nut_msion_win;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol17")]
   public class anm_msion extends MovieClip
   {
      
      private static const CCD_SEPARATE_INDEX:int = 4;
      
      public var mc_msion:nut_msion_win;
      
      private var m_mision:MovieClip = null;
      
      private var m_rankLabelCtn:Vector.<String> = new Vector.<String>();
      
      public function anm_msion()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_mision = this["mc_msion"];
         this.m_rankLabelCtn.push("d");
         this.m_rankLabelCtn.push("c");
         this.m_rankLabelCtn.push("b");
         this.m_rankLabelCtn.push("a");
         this.m_rankLabelCtn.push("s");
         var _loc1_:MovieClip = this.m_mision["mc_txt00"];
         _loc1_["txt_difi"].SetText(String(ExternalInterface.call("MessageConvert","characterselect_026")));
         _loc1_["txt_head00"].SetText(String(ExternalInterface.call("MessageConvert","eventcheck_013")));
         _loc1_["txt_head02"].SetText(String(ExternalInterface.call("MessageConvert","eventcheck_018")));
         this.m_mision["mc_page"].visible = false;
         this.m_mision["mc_rew_bg00"]["dmy_item"].Initialize();
         this.m_mision["mc_rew_bg01"]["dmy_item"].Initialize();
         this.m_mision["mc_rew_bg02"].visible = false;
         _loc1_["txt_reward02"].visible = false;
         _loc1_["txt_rew_x3"].visible = false;
         this.m_mision["all_conf_l"].stop();
         this.m_mision.stop();
         visible = false;
      }
      
      public function RequestOpenDialog(param1:int, param2:EventParam) : *
      {
         var _loc8_:Array = null;
         this.visible = true;
         var _loc3_:String = param1 > CCD_SEPARATE_INDEX ? "left" : "right";
         this.gotoAndStop(_loc3_);
         var _loc4_:MovieClip = this.m_mision["mc_txt00"];
         _loc4_["txt_client"].SetText(param2.client);
         _loc4_["txt_reward00"].SetText(param2.rewardNameCtn[0]);
         _loc4_["txt_rew_x1"].SetText(param2.rewardNumCtn[0]);
         this.m_mision["mc_rew_bg00"]["mc_item"].gotoAndStop(param2.rewardIconTypeCtn[0]);
         var _loc5_:Boolean = true;
         if(param2.rewardNameCtn[1].length > 0)
         {
            _loc8_ = new Array(param2.rewardNumCtn[1].toString());
            _loc4_["txt_reward01"].SetText(param2.rewardNameCtn[1]);
            _loc4_["txt_rew_x2"].SetText(String(ExternalInterface.call("MessageConvert","eventcheck_023")),_loc8_);
            if(param2.rewardIconTypeCtn[1].length > 0)
            {
               this.m_mision["mc_rew_bg01"]["mc_item"].visible = true;
               this.m_mision["mc_rew_bg01"]["mc_item"].gotoAndStop(param2.rewardIconTypeCtn[1]);
               this.m_mision["mc_rew_bg01"]["dmy_item"].DettachImage();
            }
            else
            {
               this.m_mision["mc_rew_bg01"]["mc_item"].visible = false;
               this.m_mision["mc_rew_bg01"]["dmy_item"].AttachImage(param2.rewardIconDataPathCtn[1]);
            }
         }
         else
         {
            _loc5_ = false;
         }
         _loc4_["txt_reward01"].visible = _loc5_;
         _loc4_["txt_rew_x2"].visible = _loc5_;
         this.m_mision["mc_rew_bg01"].visible = _loc5_;
         this.m_mision["mc_title"]["txt_title"].SetText(param2.subEventTitle);
         this.m_mision["mc_txt02"]["txt_data01"].SetText(param2.outline);
         var _loc6_:String = "none";
         if(param2.difficult < this.m_rankLabelCtn.length)
         {
            _loc6_ = this.m_rankLabelCtn[param2.difficult];
         }
         this.m_mision["mc_rate"].gotoAndStop(_loc6_);
         var _loc7_:Boolean = false;
         if(param2.stats == EventParam.CCD_SUB_EVENT_STATE_CLEAR || param2.stats == EventParam.CCD_SUB_EVENT_STATE_VISIBLED_CLEAR)
         {
            _loc7_ = true;
         }
         this.m_mision["all_conf_l"].visible = _loc7_;
         if(_loc7_ == true)
         {
            this.m_mision["all_conf_l"].gotoAndPlay("loop");
         }
         this.m_mision.gotoAndPlay("in");
      }
      
      public function RequestCloseDialog() : *
      {
         this.m_mision.gotoAndPlay("out");
      }
      
      public function IsOpenedDialog() : Boolean
      {
         return this.m_mision.currentLabel == "data_1";
      }
      
      public function IsClosedDialog() : Boolean
      {
         return this.m_mision.currentLabel == "end";
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

