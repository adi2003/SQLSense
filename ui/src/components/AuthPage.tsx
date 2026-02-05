import React, { useState } from 'react';
import { Database, Eye, EyeOff, Mail, Lock, User, Github, Chrome } from 'lucide-react';
import AuthForm from './AuthForm';
import SocialAuth from './SocialAuth';

const AuthPage: React.FC = () => {
  const [isLogin, setIsLogin] = useState(true);

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-900 via-blue-900 to-slate-800 flex items-center justify-center p-4">
      {/* Background Pattern */}
      <div className="absolute inset-0 opacity-10">
        <div className="absolute inset-0" style={{
          backgroundImage: `url("data:image/svg+xml,%3Csvg width='60' height='60' viewBox='0 0 60 60' xmlns='http://www.w3.org/2000/svg'%3E%3Cg fill='none' fill-rule='evenodd'%3E%3Cg fill='%23ffffff' fill-opacity='0.1'%3E%3Ccircle cx='5' cy='5' r='1'/%3E%3C/g%3E%3C/g%3E%3C/svg%3E")`,
        }} />
      </div>

      <div className="relative w-full max-w-md">
        {/* Header */}
        <div className="text-center mb-8">
          <div className="inline-flex items-center justify-center w-16 h-16 bg-gradient-to-r from-blue-500 to-teal-500 rounded-2xl mb-4 shadow-lg">
            <Database className="w-8 h-8 text-white" />
          </div>
          <h1 className="text-3xl font-bold text-white mb-2">
            SQL<span className="text-transparent bg-clip-text bg-gradient-to-r from-blue-400 to-teal-400">Sense</span>
          </h1>
          <p className="text-slate-400 text-sm">Smart MySQL Syntax Highlighting & Error Detection</p>
        </div>

        {/* Main Card */}
        <div className="bg-white/10 backdrop-blur-xl rounded-2xl shadow-2xl border border-white/20 overflow-hidden">
          <div className="p-8">
            {/* Mode Toggle */}
            <div className="flex bg-slate-800/50 rounded-xl p-1 mb-8">
              <button
                onClick={() => setIsLogin(true)}
                className={`flex-1 py-2 px-4 text-sm font-medium rounded-lg transition-all duration-200 ${
                  isLogin
                    ? 'bg-gradient-to-r from-blue-500 to-teal-500 text-white shadow-lg'
                    : 'text-slate-400 hover:text-white'
                }`}
              >
                Sign In
              </button>
              <button
                onClick={() => setIsLogin(false)}
                className={`flex-1 py-2 px-4 text-sm font-medium rounded-lg transition-all duration-200 ${
                  !isLogin
                    ? 'bg-gradient-to-r from-blue-500 to-teal-500 text-white shadow-lg'
                    : 'text-slate-400 hover:text-white'
                }`}
              >
                Sign Up
              </button>
            </div>

            {/* Welcome Message */}
            <div className="text-center mb-6">
              <h2 className="text-xl font-semibold text-white mb-2">
                {isLogin ? 'Welcome back!' : 'Create your account'}
              </h2>
              <p className="text-slate-400 text-sm">
                {isLogin
                  ? 'Sign in to access your SQL workspace'
                  : 'Join thousands of developers using SQLSense'}
              </p>
            </div>

            {/* Social Auth */}
            <SocialAuth isLogin={isLogin} />

            {/* Divider */}
            <div className="flex items-center my-6">
              <div className="flex-1 border-t border-slate-700"></div>
              <span className="px-4 text-slate-400 text-sm">or</span>
              <div className="flex-1 border-t border-slate-700"></div>
            </div>

            {/* Auth Form */}
            <AuthForm isLogin={isLogin} />
          </div>

          {/* Footer */}
          <div className="px-8 py-4 bg-black/20 border-t border-white/10">
            <p className="text-center text-xs text-slate-400">
              {isLogin ? (
                <>
                  New to SQLSense?{' '}
                  <button
                    onClick={() => setIsLogin(false)}
                    className="text-blue-400 hover:text-blue-300 font-medium transition-colors"
                  >
                    Create an account
                  </button>
                </>
              ) : (
                <>
                  Already have an account?{' '}
                  <button
                    onClick={() => setIsLogin(true)}
                    className="text-blue-400 hover:text-blue-300 font-medium transition-colors"
                  >
                    Sign in
                  </button>
                </>
              )}
            </p>
          </div>
        </div>

        {/* Bottom Links */}
        <div className="mt-8 text-center">
          <div className="flex justify-center space-x-6 text-xs text-slate-400">
            <a href="#" className="hover:text-white transition-colors">Terms of Service</a>
            <a href="#" className="hover:text-white transition-colors">Privacy Policy</a>
            <a href="#" className="hover:text-white transition-colors">Support</a>
          </div>
          <p className="mt-4 text-xs text-slate-500">
            🔒 Your data is encrypted and secure
          </p>
        </div>
      </div>
    </div>
  );
};

export default AuthPage;