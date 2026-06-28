package script.hist_cmn_brt
{
   import ELoader.ExtendLoader;
   import Struct.MessageParam;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import flash.net.URLRequest;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol46")]
   public class nut_lst extends MovieClip
   {
      
      public var mc_lst_1:MovieClip;
      
      public var mc_lst_2:MovieClip;
      
      public var mc_lst_3:MovieClip;
      
      public var mc_lst_4:MovieClip;
      
      public var mc_lst_5:MovieClip;
      
      public var mc_lst_6:MovieClip;
      
      public var mc_lst_7:MovieClip;
      
      public var mc_lst_8:MovieClip;
      
      internal const CCD_EPISODE_LIST_NUM:* = 8;
      
      internal const CCD_BATTLE_TYPE_INVALID:* = -1;
      
      internal const CCD_BATTLE_RANK_INVALID:* = -1;
      
      internal const CCD_LIST_TYPE_BATTLE:* = 0;
      
      internal const CCD_LIST_TYPE_OTHER:* = 1;
      
      internal const CCD_WAIT_TIME_MAX:* = 6;
      
      private var m_chapterListUi:Array = new Array(this.CCD_EPISODE_LIST_NUM);
      
      private var m_chapterInfoCtn:Vector.<Object> = new Vector.<Object>();
      
      private var m_histParam:HistParam;
      
      private var m_playerFace:Array = new Array(this.CCD_EPISODE_LIST_NUM);
      
      private var m_enemyFace:Array = new Array(this.CCD_EPISODE_LIST_NUM);
      
      private var m_curSelectIndex:int;
      
      private var m_openEpisodeNum:int;
      
      private var m_oepnChapterNum:int;
      
      private var m_waitTimer:int;
      
      public function nut_lst()
      {
         super();
         addFrameScript(12,this.frame13,16,this.frame17,20,this.frame21,24,this.frame25,28,this.frame29,37,this.frame38);
         this.m_histParam = new HistParam();
         this.m_curSelectIndex = 0;
         this.m_openEpisodeNum = 0;
         this.m_oepnChapterNum = 0;
         this.m_waitTimer = 0;
      }
      
      public function Initialize() : *
      {
         var _loc2_:* = undefined;
         var _loc1_:int = 0;
         while(_loc1_ < this.CCD_EPISODE_LIST_NUM)
         {
            _loc2_ = "mc_lst_";
            _loc2_ += String(_loc1_ + 1);
            this.m_chapterListUi[_loc1_] = this[_loc2_];
            this.m_chapterListUi[_loc1_].mc_new.visible = false;
            this.m_playerFace[_loc1_] = new ExtendLoader();
            this.m_enemyFace[_loc1_] = new ExtendLoader();
            _loc1_++;
         }
         this.Reset();
      }
      
      public function Reset() : *
      {
         var _loc1_:int = 0;
         while(_loc1_ < this.CCD_EPISODE_LIST_NUM)
         {
            this.m_chapterListUi[_loc1_].visible = false;
            this.m_playerFace[_loc1_].unload();
            this.m_enemyFace[_loc1_].unload();
            _loc1_++;
         }
         if(this.m_chapterInfoCtn.length > 0)
         {
            do
            {
               this.m_chapterInfoCtn.pop();
            }
            while(this.m_chapterInfoCtn.length > 0);
         }
         this.m_curSelectIndex = 0;
         if(this.m_chapterInfoCtn.length > 0)
         {
            do
            {
               this.m_chapterInfoCtn.pop();
            }
            while(this.m_chapterInfoCtn.length > 0);
         }
      }
      
      public function SetOpenEpisodeAndChapterNum(param1:int, param2:int) : *
      {
         this.m_openEpisodeNum = param1;
         this.m_oepnChapterNum = param2;
      }
      
      public function SetCurrentSelIndex(param1:int) : *
      {
         this.m_curSelectIndex = param1;
      }
      
      public function SetBattleChapter(param1:int, param2:int, param3:int, param4:int, param5:Boolean) : *
      {
         var _loc6_:String = null;
         var _loc7_:String = null;
         var _loc8_:String = null;
         var _loc9_:URLRequest = null;
         var _loc10_:URLRequest = null;
         var _loc11_:String = null;
         if(param2 < this.CCD_EPISODE_LIST_NUM)
         {
            this.m_chapterListUi[param2].visible = true;
            if(this.m_openEpisodeNum - 1 == param1 && this.m_oepnChapterNum <= param2)
            {
               this.m_chapterListUi[param2].visible = false;
            }
            else
            {
               this.m_chapterListUi[param2].gotoAndStop("off_btl");
               this.m_chapterListUi[param2].mc_msg.visible = false;
               _loc6_ = this.m_histParam.GetBattleIconInfo(param1,param4,HistParam.ICON_BATTLE_PLAYER);
               _loc7_ = this.m_histParam.GetBattleIconInfo(param1,param4,HistParam.ICON_BATTLE_ENEMY);
               _loc8_ = this.m_histParam.GetEpisodeRankLabel(param3);
               if(_loc8_.length == 0)
               {
                  this.m_chapterListUi[param2].mc_rslt.visible = false;
               }
               else
               {
                  this.m_chapterListUi[param2].mc_rslt.visible = true;
                  this.m_chapterListUi[param2].mc_rslt.gotoAndStop(_loc8_);
               }
               if(param5 == true)
               {
                  this.m_chapterListUi[param2].mc_up.visible = true;
               }
               else
               {
                  this.m_chapterListUi[param2].mc_up.visible = false;
               }
               _loc9_ = new URLRequest("../charicon_vs/vs_" + _loc6_ + ".xfbin");
               this.m_playerFace[param2].load(_loc9_);
               this.m_playerFace[param2].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
               this.m_chapterListUi[param2].dmy_char1.addChild(this.m_playerFace[param2]);
               _loc10_ = new URLRequest("../charicon_vs/vs_" + _loc7_ + ".xfbin");
               this.m_enemyFace[param2].load(_loc10_);
               this.m_enemyFace[param2].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
               this.m_chapterListUi[param2].dmy_char2.addChild(this.m_enemyFace[param2]);
               _loc11_ = this.m_histParam.GetBattleIconInfo(param1,param4,HistParam.ICON_BATTLE_TYPE);
               this.m_chapterListUi[param2].mc_type.gotoAndStop(_loc11_);
               this.RegistListType(this.CCD_LIST_TYPE_BATTLE);
            }
         }
      }
      
      public function SetOtherChapter(param1:int, param2:int) : *
      {
         var _loc3_:String = null;
         if(param2 < this.CCD_EPISODE_LIST_NUM)
         {
            this.m_chapterListUi[param2].visible = true;
            this.m_chapterListUi[param2].mc_msg.visible = true;
            if(this.m_openEpisodeNum - 1 == param1 && this.m_oepnChapterNum <= param2)
            {
               this.m_chapterListUi[param2].visible = false;
            }
            else
            {
               this.m_chapterListUi[param2].gotoAndStop("off_mov");
               _loc3_ = this.m_histParam.GetEpisodeMessageId(param1,param2);
               if(_loc3_ != "main_outline_01000")
               {
                  this.m_chapterListUi[param2].mc_msg.txt_msg.SetText(MessageParam(ExternalInterface.call("MessageConvertParam",_loc3_)).m_msg);
               }
               else
               {
                  this.m_chapterListUi[param2].mc_msg.txt_msg.SetText(ExternalInterface.call("MessageConvert",_loc3_));
               }
               this.RegistListType(this.CCD_LIST_TYPE_OTHER);
            }
         }
      }
      
      private function RegistListType(param1:int) : *
      {
         var _loc2_:Object = new Object();
         _loc2_.type = param1;
         this.m_chapterInfoCtn.push(_loc2_);
      }
      
      public function StartSelect() : *
      {
         if(this.m_chapterInfoCtn[this.m_curSelectIndex].type == this.CCD_LIST_TYPE_BATTLE)
         {
            this.m_chapterListUi[this.m_curSelectIndex].gotoAndPlay("on_btl");
         }
         else
         {
            this.m_chapterListUi[this.m_curSelectIndex].gotoAndPlay("on_mov");
         }
      }
      
      public function StopSelect() : *
      {
         if(this.m_chapterInfoCtn[this.m_curSelectIndex].type == this.CCD_LIST_TYPE_BATTLE)
         {
            this.m_chapterListUi[this.m_curSelectIndex].gotoAndStop("off_btl");
         }
         else
         {
            this.m_chapterListUi[this.m_curSelectIndex].gotoAndStop("off_mov");
         }
      }
      
      public function NextChapter() : Boolean
      {
         var _loc1_:Boolean = false;
         trace("m_chapterInfoCtn.length : " + this.m_chapterInfoCtn.length);
         if(this.m_waitTimer == 0 && this.m_curSelectIndex + 1 < this.m_chapterInfoCtn.length)
         {
            if(this.m_chapterInfoCtn[this.m_curSelectIndex].type == this.CCD_LIST_TYPE_BATTLE)
            {
               this.m_chapterListUi[this.m_curSelectIndex].gotoAndStop("off_btl");
            }
            else
            {
               this.m_chapterListUi[this.m_curSelectIndex].gotoAndStop("off_mov");
            }
            ++this.m_curSelectIndex;
            if(this.m_chapterInfoCtn[this.m_curSelectIndex].type == this.CCD_LIST_TYPE_BATTLE)
            {
               this.m_chapterListUi[this.m_curSelectIndex].gotoAndPlay("on_btl");
            }
            else
            {
               this.m_chapterListUi[this.m_curSelectIndex].gotoAndPlay("on_mov");
            }
            _loc1_ = true;
            this.m_waitTimer = this.CCD_WAIT_TIME_MAX;
         }
         return _loc1_;
      }
      
      public function PrevChapter() : Boolean
      {
         var _loc1_:Boolean = false;
         if(this.m_waitTimer == 0 && this.m_curSelectIndex > 0)
         {
            if(this.m_chapterInfoCtn[this.m_curSelectIndex].type == this.CCD_LIST_TYPE_BATTLE)
            {
               this.m_chapterListUi[this.m_curSelectIndex].gotoAndStop("off_btl");
            }
            else
            {
               this.m_chapterListUi[this.m_curSelectIndex].gotoAndStop("off_mov");
            }
            --this.m_curSelectIndex;
            if(this.m_chapterInfoCtn[this.m_curSelectIndex].type == this.CCD_LIST_TYPE_BATTLE)
            {
               this.m_chapterListUi[this.m_curSelectIndex].gotoAndPlay("on_btl");
            }
            else
            {
               this.m_chapterListUi[this.m_curSelectIndex].gotoAndPlay("on_mov");
            }
            _loc1_ = true;
            this.m_waitTimer = this.CCD_WAIT_TIME_MAX;
         }
         return _loc1_;
      }
      
      public function UpdateChangeChapter() : *
      {
         if(this.currentLabel == "next")
         {
            this.gotoAndPlay("next_in");
         }
         else if(this.currentLabel == "back")
         {
            this.gotoAndPlay("back_in");
         }
      }
      
      public function IsBattleChapter() : Boolean
      {
         var _loc1_:Boolean = false;
         if(this.m_chapterInfoCtn[this.m_curSelectIndex].type == this.CCD_LIST_TYPE_BATTLE)
         {
            _loc1_ = true;
         }
         return _loc1_;
      }
      
      public function GetChapterIndex() : int
      {
         return this.m_curSelectIndex;
      }
      
      public function PlayDecideAnm() : *
      {
         if(this.m_chapterInfoCtn[this.m_curSelectIndex].type == this.CCD_LIST_TYPE_BATTLE)
         {
            this.m_chapterListUi[this.m_curSelectIndex].gotoAndPlay("enter_btl");
         }
         else
         {
            this.m_chapterListUi[this.m_curSelectIndex].gotoAndPlay("enter_mov");
         }
      }
      
      public function UpdateWaitTimer() : *
      {
         if(this.m_waitTimer > 0)
         {
            --this.m_waitTimer;
         }
      }
      
      internal function frame13() : *
      {
         this.stop();
      }
      
      internal function frame17() : *
      {
         this.stop();
      }
      
      internal function frame21() : *
      {
         gotoAndStop("loop");
      }
      
      internal function frame25() : *
      {
         this.stop();
      }
      
      internal function frame29() : *
      {
         gotoAndStop("loop");
      }
      
      internal function frame38() : *
      {
         this.stop();
      }
   }
}

