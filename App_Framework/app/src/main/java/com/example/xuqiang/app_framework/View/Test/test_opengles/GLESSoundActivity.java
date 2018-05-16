package com.example.xuqiang.app_framework.View.Test.test_opengles;

import android.content.Context;
import android.media.AudioFocusRequest;
import android.media.AudioManager;
import android.media.SoundPool;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.example.libcore.log.L;
import com.example.libcore.toast.T;
import com.example.libcore_ui.activity.BaseActivity;
import com.example.xuqiang.app_framework.R;

import java.util.HashMap;

public class GLESSoundActivity extends BaseActivity {
    SoundPool soundPool;                // 声明SoundPool的引用
    HashMap<Integer, Integer> hashMap;  // 声明hashmap来存放声音文件
    int currentStreamID;                // 当前正在播放streaid
    private AudioManager mAudioManager;
    private Button btn_test_opengles_sound_play;
    private Button btn_test_opengles_sound_pause;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_test_opengles_sound);
        mAudioManager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
        AudioFocusRequest focusRequest;
        initSoundPool();
        btn_test_opengles_sound_play = (Button)this.findViewById(R.id.btn_test_opengles_sound_play);
        btn_test_opengles_sound_play.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mAudioManager.requestAudioFocus(mAudioFocusListener,
                        AudioManager.STREAM_MUSIC,AudioManager.AUDIOFOCUS_GAIN); // 获取源
                playSound(1, 0);
                T.getInstance().showShort("播放即时音效");
            }
        });

        btn_test_opengles_sound_pause = (Button)this.findViewById(R.id.btn_test_opengles_sound_pause);
        btn_test_opengles_sound_pause.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mAudioManager.abandonAudioFocus(mAudioFocusListener); // 释放源
                soundPool.stop(currentStreamID);
                T.getInstance().showShort("停止播放音效");
            }
        });
    }
    protected void initSoundPool(){
        soundPool = new SoundPool(4, AudioManager.STREAM_MUSIC, 0); // 创建SoundPool对象
        hashMap = new HashMap<Integer, Integer>(); // 创建HashMap对象
        hashMap.put(1, soundPool.load(this, R.raw.musictest, 1));
    }
    public void playSound(int sound, int loop){
        AudioManager audioManager = (AudioManager)this.getSystemService(Context.AUDIO_SERVICE); // 获取AudioManager对象
        if (audioManager != null){
            float streamVolumeCurrent = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC); // 获取当前音量
            float streamVolumeMax = audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC); // 获取系统最大音量
            float volume = streamVolumeCurrent / streamVolumeMax; // 计算得到的播放音量
            // 调用soundpool的play方法来播放声音
            currentStreamID = soundPool.play(hashMap.get(sound), volume, volume, 1, loop, 1.0f);
        }
    }
    public AudioManager.OnAudioFocusChangeListener mAudioFocusListener = new AudioManager.OnAudioFocusChangeListener() {
        public void onAudioFocusChange(int focusChange) {
            // AudioFocus is a new feature: focus updates are made verbose on purpose
            switch (focusChange) {
                case AudioManager.AUDIOFOCUS_LOSS:
                    L.d("Test", "AudioFocus: received AUDIOFOCUS_LOSS");
                    break;
                case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT:
                    L.d("Test", "AudioFocus: received AUDIOFOCUS_LOSS_TRANSIENT");
                    break;
                case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK:
                    L.d("Test", "AudioFocus: received AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK");
                    break;
                case AudioManager.AUDIOFOCUS_GAIN:
                    L.d("Test", "AudioFocus: received AUDIOFOCUS_GAIN");
                    break;
                default:
                    L.d("Test", "Unknown audio focus change code");
            }
        }
    };
}
